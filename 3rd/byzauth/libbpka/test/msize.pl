#!/usr/bin/perl 

$n = 0.0; 
while($line = <STDIN>)
{
	chomp $line; 
	if( $line =~ /received (\d*) bytes/ ) { 
		$size += int($1);
		$n += 1.000000 ; 
	}
}

print $size/$n ;  
