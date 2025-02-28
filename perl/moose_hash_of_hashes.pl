package Something;

use Moose;
use Data::Dumper;

has dates_checked_by_reported_partner_no => (
    is => 'rw', 
    isa => 'HashRef[HashRef[Str]]',
    default => sub { {} },
);

sub dates($self)
{
    my($self) = @_;

    $self->dates_checked_by_reported_partner_no->{XtnDaysByBlahBlah} = {
        first_xtn_day => '2014-01-01',
        last_xtn_day  => '2014-02-01'
    };

    print Dumper($self->dates_checked_by_reported_partner_no());
}

package main;

my $something = Something->new();
$something->dates();
