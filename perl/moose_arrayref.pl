package Test;
use Moose;

has 'a' => ( 
    is => 'rw', 
    isa => 'ArrayRef', 
    default => sub { [] }, 
);

no Moose;

package main;
use Data::Dumper;

my $s = Test->new();

print "a: " . Dumper($s->a());
push @{ $s->a }, qw/ a b c /;

my $idx = 0;
for my $x ( @{ $s->a } ) {
  print $idx++, ": $x\n";
}

exit 0;
