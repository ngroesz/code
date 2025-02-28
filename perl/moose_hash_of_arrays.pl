package Something;

use Moose;

has reported_cable_systems_by_division => (
    is => 'rw', 
    isa => 'HashRef[ArrayRef[Int]]',
    default => sub { [] },
);

sub stuff
{
    my($self) = @_;

    $self->dates_checked_by_reported_partner_no->{100} = {'2014-01-01' => 1};

    if ($self->dates_checked_by_reported_partner_no->{100}{'2014-01-01'}) {
        print "Yeaeeaeh!\n";
    }
    if ($self->dates_checked_by_reported_partner_no->{100}{'2014-01-02'}) {
        print "Noooo!\n";
    }
    #$self->set_reported_partner_date(100, '2014-01-01');
}

package main;

my $something = Something->new();
$something->stuff();
