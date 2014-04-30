#!/usr/bin/perl 




$i = 0;
while( $line = <STDIN> ) 
{
	chomp $line; 

   # for the cache records
	if( $line=~ /CacheSizePeak=(\d*)/ ) 
	{
		$size = $1; 
		if( $line =~ /LocalTime=(\d*)/ ) 
		{
			$time = $1; 
			print "$time  $size\n" ; 
			$i++; 
		}
	}

	next; 

	# for timestamps 
   if( $line =~ /messagecache.cpp 153/ ) 
   {
       if( $line =~ /LT=(\d*)  SR=(\d*)/ ) 
       {
           print "$i   $1   $2\n" ; 
           $i++; 
       }
   }

} 
