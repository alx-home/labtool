#! /bin/sh
exec perl -n -w -x $0 ${1+"$@"}
#! perl -n
#line 5

if (eof) { close ARGV; $in_paren=$in_cout=''; }
next if (m/^#/ || m/^\s*$/);
s+\\.+X+g;
s+\".*?\"+X+g;
s+\'.\'+X+g;
s+//.*++;
next if (m/^\s*$/);
m/^( *)(.?)(.?)/; $indent=length($1); $in_cout = '' unless ($2.$3 eq '<<');
++$indent if ($2 eq ')');
print "vi +$. $ARGV\n" if (($in_paren && $paren_indent != $indent) || ($in_cout && $cout_indent != $indent));
$paren_indent=$indent;

if ($in_paren)
{
  $in_paren = m/^([^()]*(\([^()]*\))*)*$/;
}
elsif (m/^([^()]*\( *)(([^()]*(\([^()]*\))*)*)$/ && length($2) > 1)
{
  $paren_indent=length($1); $in_paren=1;
}

if (m/^( *\w+ *)<</)
{
  $cout_indent=length($1); $in_cout=1;
}
