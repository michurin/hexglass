#!/usr/local/bin/perl

use strict;

sub readfile {
    my ($f) = @_;
    open FH, "<$f" or die "$! $f";
    my $d = join('', <FH>);
    close FH;
    return $d;
}

sub savefile {
    my ($f, $d) = @_;
    open FH, ">$f" or die "$! $f";
    print FH $d;
    close FH;
}

sub exp_tabs {
    my ($f) = @_;
    my $d = readfile("$f");
    $d=~s/^\s+//;
    $d=~s/\s+$//;
    my $r = join('', map {
      1 while s/\t+/' ' x (length($&) * 8 - length($`) % 8)/e;
      s/\s+$//;
      "$_\n"
    } split("\n", $d));
    savefile($f, $r);
}

sub fix_header {
    my ($f) = @_;
    my $m = uc($f);
    $m=~s/^[^A-Z]+//;
    $m=~s/[^A-Z]/_/g;
    my $d = readfile("$f");
    $d=~m-^(/\*.*?\*/\s+)(.*)$-sm;
    my $c=$1;
    my $b=$2;
    $b=~s/\s*#ifndef[^\n]+\n//;
    $b=~s/\s*#define[^\n]+\n//;
    $b=~s/\n#endif[^\n]+\s*$//;
    savefile($f, qq|$c#ifndef $m\n#define $m\n$b\n#endif // $m\n|);
}

sub margs {
    my ($f) = @_;
    my $d = readfile("$f");
    foreach (split("\n", $d)) {
        m/^( *)/;
        if (length($1) % 4) {
            print "$f: $_\n";
        }
    }
}

sub check_dir {
    my ($d) = @_;
    my @a = <$d/*>;
    foreach (@a) {
        if (-d $_) {
            check_dir($_);
        } else {
            my $h = m/\.h$/;
            my $c = m/\.cpp$/;
            print "file $_\n";
            if ($h or $c) {
                exp_tabs($_);
                margs($_);
            }
            if ($h) {
                fix_header($_)
            }
        }
    }
}

print "Check src-tree\n";
check_dir('../src');

print "Check <MANIFEST>\n";
open M, '<../MANIFEST' or die;
while (<M>) {
    chomp;
    if ($_ eq 'README' or $_ eq 'CHANGES' or m/\.(cpp|h|pro|qrc|rc)$/) {
        print "proc $_\n";
        my $f = "../$_";
        my $d = '';
        open F, "<$f" or die;
        while (<F>) {
            s/\s+$//;
            $d .= "$_\n";
        }
        close F;
        $d =~ s/\n+$/\n/;
        open F, ">$f" or die;
        print F $d;
        close F;
    } else {
        print "left $_\n";
    }
}
close M;
