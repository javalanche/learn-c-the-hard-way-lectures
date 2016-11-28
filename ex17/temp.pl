#! /usr/bin/perl -w

# use Term::ANSIColor;

$color_funcname = "\e[38;5;9m";
$color_in_funcname = "\e[3;31m";
$color_filename = "\e[1;33m";
$color_lineno = "\e[1;34m";
$color_title = "\e[38;5;10m";
$color_reset = "\e[0m";
$color_bg_at = "\e[48;5;236m";
# $bg_reset = "\e[49m";
# $fg_reset = "\e[39m";

$#ARGV != -1 && (open(STDIN, "<$ARGV[0]") || exit 1);

while(<STDIN>)
{
    if (m/^(==\d+== +(?:by|at) 0x(?:[A-F]|\d)+: )(.+) \(in (.+)\)$/)
    {
        $bg = index($1, 'at') == -1 ? "" : $color_bg_at;
        print(
            $bg, $1, $color_funcname, $2, $color_reset, $bg, ' (in ',
            $color_in_funcname, $3, $color_reset, ")\n"
        )
    }
    elsif (m/^(==\d+== +(?:by|at) 0x(?:[A-F]|\d)+: )(.+) \((.+):([0-9]+)\)$/)
    {
        $bg = index($1, 'at') == -1 ? "" : $color_bg_at;
        print(
            $bg, $1, $color_funcname, $2, $color_reset, $bg, ' (',
            $color_filename, $3, $color_reset, $bg, ':', $color_lineno,
            $4, $color_reset, ")\n"
        )
    }
    elsif (m/^(==\d+== [A-Z].+?:)(.+)$/)
    {
        print($color_title, $1, $color_reset, $2, "\n")
    }
    else
    {
        print($_)
    }
}
