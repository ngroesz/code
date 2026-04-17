use warnings;
use strict;

sub uniq
{
    my %seen;
    grep !$seen{$_}++, @_;
}

my $filename = $ARGV[0];

open(my $fh, '<:encoding(latin-1)', $filename)
    || die "cannot open $filename: $!";

my @unique_chars;

while(<$fh>) {
    my $line = $_;
    my @line_chars = map { substr($line, $_, 1) } 0 .. length($line) - 1;

    @unique_chars = uniq(@unique_chars, @line_chars);
}

close($fh);


foreach my $char (@unique_chars) {
    print "char: $char\tvalue: @{[ ord($char) ]}\n";
}

