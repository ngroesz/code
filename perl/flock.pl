#!/usr/local/bin/vod_perl

use warnings;
use strict;

use Fcntl ':flock';

use constant LOCK_FILE => 'lock_file.lock';

sub get_exclusive_lock
{
    open(my $lock_fh, '>>', LOCK_FILE) || die "Cannot open @{[LOCK_FILE]} for writing: $!\n";
    flock($lock_fh, LOCK_EX | LOCK_NB) || die "Cannot lock @{[LOCK_FILE]} exclusively: $!\n";
    return $lock_fh;
}

my $lock_fh = get_exclusive_lock();

print "got the lock\n";
until (<STDIN>) {
    sleep 1;
}

