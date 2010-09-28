#!/usr/local/bin/wish8.4

# TODO
# - цвета (?)
# - запуск фигур с максимальной высоты
# - очки/уровни
# - рекорды
# - убрать диагностику и лишние бинды
# - цвет заполнения наврено не надо задавать вообще
#   при создании, он задаётся стразу же при сбросе элементов

set area_w    13
set area_h    25
set time      500
set item_r    0
set item_l    0
set item_dl   1
set item_type 0
set item_ang  0
set item_next 0
set lines_complete 0
set step_drop_mode 1

proc create_all_items {} {
  set all [list]
  foreach {p} {{0 -2 0 -1 0 0 0 1}
                {-1 0 0 1 1 1 1 0}
	       {0 0 -1 0 0 1 1 1}
	        {0 0 -1 0 1 1 0 -1}
               {0 -2 0 -1 0 0 1 1}
               {0 -2 0 -1 0 0 -1 0}
	        {0 -1 0 0 0 1 1 1}
	        {0 -1 0 0 0 1 -1 0}
	       {1 1 0 0 -1 0 -2 -1}
	       {2 1 1 1 0 0 -1 0}} {
    set one [list]
    for {set i 0} {$i<6} {incr i} {
      lappend one $p
      set pt [list]
      foreach {x y} $p {
        lappend pt $y [expr {$y-$x}]
      }
      lset p $pt
    }
    lappend all $one
  }
  return $all
}

set item [create_all_items]
#                   ----      C         <>        T 
#                   \___      ___/      V~        ~V
#                   /\/\      \/\/
set item_clr [list {#ff0000} {#ff6600} {#ffff00} {#66ff66} \
                   {#ff9900} {#66ff00} {#00ffff} {#9999ff} \
		   {#9900ff} {#ff00ff}]
#     r=0 1  2  3  4
#      |_ |  |_ |  |_
#   6-/  \|_/  \|_/  \
#   5----/  \__/  \__/
#   4-/  \__/  \__/  \
#   3----/  \__/  \__/
#   2-/  \__/  \
#   1----/  \__/  (r, l)
# l=0-/00\__/  \
#     \__/  \__/
#
# x=r
# y=[(l+r)/2]
#
#  \__/
#  /  \03  (x, y)
#  \__/
#  /  \02
#  \__/
#  /  \01
#  \__/   __    __    __    __
#  /* \__/* \__/* \__/* \__/* \__
#  \__/* \__/* \__/* \__/* \__/* \
# 00  \__/  \__/  \__/  \__/  \__/
#    10  \__/  \__
#       20  \__/  \__
#          30  \__/  \
#                 \__/
#
#   1__2
#  /    \
# 0      3
#  \    /
#   5~~4
#
proc create_field {cnv w h a b c clr_bg clr_fill clr_ol} {
  set aa [expr {$a+$a}]
  set aab [expr {$aa+$b}]
  canvas $cnv -width [expr {$w*$aab+$b+1}] \
              -height [expr {($h*2+1)*$c+1}] \
              -bg $clr_bg \
	      -highlightthickness 0
  for {set x 0} {$x<$w} {incr x} {
    set yi [expr {$x/2}]
    set yf [expr {$yi+$h}]
    for {set y $yi} {$y<$yf} {incr y} {
      set x0 [expr {$x*$aab}]
      set y0 [expr {(2*($h-$y)+$x-1)*$c}]
      set x1 [expr {$x0+$b}]
      set y1 [expr {$y0-$c}]
      set x2 [expr {$x1+$aa}]
      set x3 [expr {$x2+$b}]
      set y4 [expr {$y0+$c}]
      $cnv create polygon $x0 $y0 \
                          $x1 $y1 \
		          $x2 $y1 \
		          $x3 $y0 \
		          $x2 $y4 \
		          $x1 $y4 \
		          -fill $clr_fill \
		          -width 1 \
		          -outline $clr_ol \
			  -tag "h${x}x$y"
#      $cnv bind "h${x}x$y" <Button-1> [list puts "h${x}x$y"]
    }
  }
}

proc create_top_menu {} {
  set m [menu .root_menu -tearoff 0]
  set g [menu $m.game -tearoff 0]
  $m add cascade -label {Game} -menu $g
  foreach {l cmd a c} {{New game}  1 n reinit_game
                       {Pause}     1 p {bind_fig 0; stop_down}
                       {Unpause}   1 u {bind_fig 1; init_down}
		       {Step drop} 0 s step_drop_mode
                       {About}     1 a {show_about}
		       {Exit}      1 q exit} {
    if {$cmd == 1} {
      $g add command -label $l -accelerator $a -command $c
      bind . <Key-$a> $c
    } else {
      $g add checkbutton -label $l -accelerator $a -variable $c
      bind . <Key-$a> invert_drop_mode
    }
  }
  return $m
}

proc show_about {} {
  tk_dialog .about About {The xTetris Game
v. 1.2
Copyright (c) 2006-2007 Michurin Alexey
This program is free software; you can redistribute it and/or\
modify it under the terms of the GNU General Public License.
This program is distributed in the hope that it will be useful, but\
WITHOUT ANY WARRANTY.} {} 0 Close
}

proc invert_drop_mode {} {
  global step_drop_mode
  set step_drop_mode [expr {1-$step_drop_mode}]
}

proc bind_fig {f} {
  foreach {ev act} {<Key-Right> {move_lr   1}
                    <Key-Left>  {move_lr  -1}
		    <Key-Down>  {move_rot  1}
		    <Key-Up>    {move_rot -1}
		    <Key-space> {drop_down}} {
    bind . $ev [expr {$f?$act:{}}]
  }
}

proc create_all {} {
  global area_w area_h
  create_field .game $area_w $area_h 4 4 7 {#515151} {#000000} {#515151}
  pack .game -side left
  create_field .next 5 4 4 4 7 {#515151} {#515151} {#515151}
  pack [label .label_next -text Next: -fg {#999999} -bg {#515151}]
  pack .next -side top
  pack [label .label_lines -text Lines: -fg {#999999} -bg {#515151}] -side top
  pack [label .label_count -textvariable lines_complete -fg {#ffffff} -bg {#515151}] -side top
  pack [label .label_vers -text {xTetris v1.2} -fg {#999999} -bg {#515151}] -side bottom
  . configure -menu [create_top_menu] -bg {#515151}
  wm title . {xTetris}
  wm resizable . 0 0
  set_show_next
}

################# PREVIEW

proc set_show_next {} {
  global item item_next item_clr
  set item_next [expr {int(rand()*10)}]
  set c [lindex $item_clr $item_next]
  .next itemconfigur all -fill {#515151}
  foreach {dx dy} [lindex [lindex $item $item_next] 0] {
    set x [expr {$dx+2}]
    set y [expr {$dy+3}]
    .next itemconfigur "h${x}x$y" -fill $c
  }
}

################# MOVE

proc get_path {} {
  global item item_type item_ang item_r item_l
  set p [list]
  foreach {dx dy} [lindex [lindex $item $item_type] $item_ang] {
    set x [expr {$item_r+$dx}]
    set y [expr {($item_r+$item_l)/2+$dy}]
    lappend p "h${x}x$y"
  }
  return $p
}

proc draw_one {t c} {
  .game itemconfigur $t -fill $c
}

proc draw_path {f} {
  global item_type item_clr
  set c [expr {$f?[lindex $item_clr $item_type]:{#000000}}]
  foreach {t} [get_path] {draw_one $t $c}
}

proc read_one {t} {
  return [.game itemcget $t -fill]
}

proc read_path {} {
  foreach {t} [get_path] {
    if {[read_one $t] != {#000000}} { return 0 }
  }
  return 1
}

proc stop_down {} {
  foreach {id} [after info] {
    if {[lindex [after info $id] 0] == {move_down}} {
      after cancel $id
    }
  }
}

proc drop_down {} {
  global time step_drop_mode
  if {$step_drop_mode} {
    stop_down
    move_down_one
    init_down
  } else {
    stop_down
    set time 20
    init_down
  }
}

proc init_down {} {
  global time
  after $time move_down
}

proc move_down_one {} {
  global item_l
  draw_path 0
  incr item_l -2
  set r [read_path]
  if {$r} {
    draw_path 1
  } else {
    incr item_l 2
    draw_path 1
    analyz
    init_unit
  }
  return $r
}

proc move_down {} {
  if {[move_down_one]} init_down
}

proc move_rot {da} {
  global item_ang item_r item_l item_dl
  draw_path 0
  set a $item_ang
  set item_ang [expr {($item_ang+$da+6)%6}]
  if {![read_path]} {
    if {[move_try {1 -1 -1 -1 1 1 -1 1 2 0 -2 0}]} {
      set item_ang $a
    }
  }
  draw_path 1
}

proc move_try {drdl} {
  global item_r item_l item_dl
  foreach {dr dl} $drdl {
#    puts "$dr $dl"
    set sv [list $item_r $item_l $item_dl]
    set item_r [expr {$item_r+$dr}]
    set item_l [expr {$item_l+$dl}]
    set item_dl $dl
    if {[read_path]} {return 0}
    foreach {item_r item_l item_dl} $sv {}
  }
  return 1
}

proc move_lr {dr} {
  global item_dl
  draw_path 0
  move_try [list $dr [expr {-$item_dl}] $dr $item_dl]
  draw_path 1
}

##################### INIT

proc init_unit {} {
  global item_next \
         item_r item_l item_dl item_ang item_type \
         area_w area_h \
	 lines_complete time
  set item_r    [expr {$area_w/2}]
  set item_l    [expr {$area_h*2-4}]
  set item_dl   1
  set item_type $item_next
  set item_ang  0
  set time [expr {20000/(20+$lines_complete)}]
#  puts "$time"
  set p [read_path]
  draw_path 1
  set_show_next
  if {$p} {
    bind_fig 1
    init_down
  } else {
    bind_fig 0
  }
}

proc reinit_game {} {
  global lines_complete
  set lines_complete 0
  foreach {id} [after info] {after cancel $id}
  .game itemconfigur all -fill {#000000}
  init_unit
}

####################### ANALYZ

proc analyz {} {
  global area_w area_h lines_complete
  for {set y 0} {$y<$area_h} {incr y} {
#    puts "y=$y"
    set pt [list]
    for {set x 0} {$x<$area_w} {incr x} {
      set yy [expr {$y+$x/2}]
      lappend pt "h${x}x$yy"
    }
    set c 1
    foreach p $pt {
      if {[read_one $p] == {#000000}} {
        set c 0
	break
      }
    }
    if {$c} {
      incr lines_complete
      foreach p $pt {
        draw_one $p {#000000}
      }
      after 100 [list analyz_shift $y]
      break
    }
  }
}

proc analyz_shift {yo} {
  global area_w area_h
  set yf [expr {$area_h-1}]
  draw_path 0
  for {set y [expr {$yo}]} {$y<$yf} {incr y} {
    for {set x 0} {$x<$area_w} {incr x} {
      set ys [expr {$y+$x/2+1}]
      set yt [expr {$y+$x/2}]
      draw_one "h${x}x$yt" [read_one "h${x}x$ys"]
    }
  }
  draw_path 1
  after 300 analyz
}

####################### INIT WINDOW

create_all

####################### MAIN

init_unit
