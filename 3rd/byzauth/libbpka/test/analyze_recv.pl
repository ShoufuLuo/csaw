#!/usr/bin/perl 

while( $line = <STDIN> ) 
{
	chomp $line ; 

	if( $line =~ /received authentication vote/ ) { 
		if($line =~ /self (\S*)/ ) { 
			if( exists($count{$1}) ) { 
				$count{$1}++ ; 
			}
			else { 
				$count{$1} = 1; 
			}
		}
	}
}

while ( my ($key, $value) = each(%count) ) {
	print "$key => $value\n";
}

