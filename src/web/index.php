<?php

$hex = array(
	'00', '01', '02', '03', '04', '05', '06', '07', '08', '09', '0a', '0b', '0c', '0d', '0e', '0f', 
	'10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '1a', '1b', '1c', '1d', '1e', '1f', 
	'20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '2a', '2b', '2c', '2d', '2e', '2f', 
	'30', '31', '32', '33', '34', '35', '36', '37', '38', '39', '3a', '3b', '3c', '3d', '3e', '3f', 
	'40', '41', '42', '43', '44', '45', '46', '47', '48', '49', '4a', '4b', '4c', '4d', '4e', '4f', 
	'50', '51', '52', '53', '54', '55', '56', '57', '58', '59', '5a', '5b', '5c', '5d', '5e', '5f', 
	'60', '61', '62', '63', '64', '65', '66', '67', '68', '69', '6a', '6b', '6c', '6d', '6e', '6f', 
	'70', '71', '72', '73', '74', '75', '76', '77', '78', '79', '7a', '7b', '7c', '7d', '7e', '7f', 
	'80', '81', '82', '83', '84', '85', '86', '87', '88', '89', '8a', '8b', '8c', '8d', '8e', '8f', 
	'90', '91', '92', '93', '94', '95', '96', '97', '98', '99', '9a', '9b', '9c', '9d', '9e', '9f', 
	'a0', 'a1', 'a2', 'a3', 'a4', 'a5', 'a6', 'a7', 'a8', 'a9', 'aa', 'ab', 'ac', 'ad', 'ae', 'af', 
	'b0', 'b1', 'b2', 'b3', 'b4', 'b5', 'b6', 'b7', 'b8', 'b9', 'ba', 'bb', 'bc', 'bd', 'be', 'bf', 
	'c0', 'c1', 'c2', 'c3', 'c4', 'c5', 'c6', 'c7', 'c8', 'c9', 'ca', 'cb', 'cc', 'cd', 'ce', 'cf', 
	'd0', 'd1', 'd2', 'd3', 'd4', 'd5', 'd6', 'd7', 'd8', 'd9', 'da', 'db', 'dc', 'dd', 'de', 'df', 
	'e0', 'e1', 'e2', 'e3', 'e4', 'e5', 'e6', 'e7', 'e8', 'e9', 'ea', 'eb', 'ec', 'ed', 'ee', 'ef', 
	'f0', 'f1', 'f2', 'f3', 'f4', 'f5', 'f6', 'f7', 'f8', 'f9', 'fa', 'fb', 'fc', 'fd', 'fe', 'ff'
);

$mazeWidth = 32;
$mazeHeight = 32;

$masterMaze = array();

for ( $x = 0; $x < $mazeWidth; $x ++ ) {
	for ( $y = 0; $y < $mazeHeight; $y ++ ) {
		$masterMaze[$x][$y] = array( 'div' => 0 );
	}
}

function subDivideAreas( $divNumber, $numSubs ) {

	global $mazeWidth;
	global $mazeHeight;
	
	global $masterMaze;
	
	$maze = array();
	
	$min = 0;
	$max = 0;

	$absMin = $numSubs + 1;
	$absMax = 0;

	$xCenter = rand($mazeWidth/2-$mazeWidth/8,$mazeWidth/2+$mazeWidth/8);
	$yCenter = rand($mazeHeight/2-$mazeHeight/8,$mazeHeight/2+$mazeHeight/8);
	$slope = $mazeWidth*$mazeHeight*rand(10, 20) / 1000;
	$xSlope = rand(50, 150) / 1000;
	$ySlope = rand(50, 400) / 1000;

	// generate terrain
	for ( $x = 0; $x < $mazeWidth; $x ++ ) {
		for ( $y = 0; $y < $mazeHeight; $y ++ ) {
			$vv = ($slope*$x*($xSlope*($xCenter + $x)*($xCenter - $x) + $ySlope*($yCenter - $y)*($yCenter - $y)));
			$fl = $x*1.5;
			
			$maze[$x][$y] = (int)($vv > $fl ? $vv : $fl);
			
			if ( $maze[$x][$y] > $max ) $max = $maze[$x][$y];
			if ( $maze[$x][$y] < $min ) $min = $maze[$x][$y];
		}
	}
	
	$range = $max - $min;
	$subRanges = (int)($range / $numSubs);
	
	// clip values to number of subdivisions
	for ( $x = 0; $x < $mazeWidth; $x ++ ) {
		for ( $y = 0; $y < $mazeHeight; $y ++ ) {
			$maze[$x][$y] = (int)((( $maze[$x][$y] - $min ) / $range) * ($numSubs - 1));
		}
	}
	
	$min = 0;
	$max = 0;
	
	// blur cliped values
	for ( $i = 0; $i < 50; $i ++ ) {
		for ( $x = 1; $x < $mazeWidth - 1; $x ++ ) {
			for ( $y = 1; $y < $mazeHeight - 1; $y ++ ) {
				$maze[$x][$y] += $maze[$x-1][$y-1];
				$maze[$x][$y] += $maze[$x-1][$y];
				$maze[$x][$y] += $maze[$x-1][$y+1];
				$maze[$x][$y] += $maze[$x][$y-1];
				$maze[$x][$y] += $maze[$x][$y+1];
				$maze[$x][$y] += $maze[$x+1][$y-1];
				$maze[$x][$y] += $maze[$x+1][$y];
				$maze[$x][$y] += $maze[$x+1][$y-1];
				$maze[$x][$y] /= 9;
				
				if ( $maze[$x][$y] > $max ) $max = $maze[$x][$y];
				if ( $maze[$x][$y] < $min ) $min = $maze[$x][$y];
			}
		}
	}
	
	$range = $max - $min + 1;
	$subRanges = (int)($range / $numSubs);
	
	// clip values to number of subdivisions
	for ( $x = 0; $x < $mazeWidth; $x ++ ) {
		for ( $y = 0; $y < $mazeHeight; $y ++ ) {
			if ( $masterMaze[$x][$y]['div'] == $divNumber ) {
				$masterMaze[$x][$y]['div'] = (int)((( $maze[$x][$y] - $min ) / $range) * ($numSubs - 1));
			}
		}
	}
}

$numSubs = 5;

// generate maze height map
subDivideAreas( 0, $numSubs );
for ( $i = 0; $i < $numSubs; $i ++ ) {
	subDivideAreas( $i, 10 );
}



$absMin = 1000;
$absMax = -1000;

for ( $x = 0; $x < $mazeWidth; $x ++ ) {
	for ( $y = 0; $y < $mazeHeight; $y ++ ) {
		if ( $masterMaze[$x][$y]['div'] > $absMax ) $absMax = $masterMaze[$x][$y]['div'];
		if ( $masterMaze[$x][$y]['div'] < $absMin ) $absMin = $masterMaze[$x][$y]['div'];
	}
}

?>
<table border="0" style="margin:10% auto; border-collapse:collapse;">
<?php for( $x = 0; $x < $mazeWidth; $x ++ ) :?>
	<tr>
	<?php for( $y = 0; $y < $mazeHeight; $y ++ ) :
		$tone = (int)(255 * ( $masterMaze[$x][$y]['div'] - $absMin ) / ( $absMax - $absMin + 1 ));
	?>
		<td style="
			width:16px;
			height:16px;
			background-color:#<?php echo $hex[$tone],$hex[$tone],$hex[$tone];  ?>;
			border-top:<?php echo $masterMaze[$x][$y]['top'] ? "none" : "2px solid #00f" ?>;
			border-right:<?php echo $masterMaze[$x][$y]['right'] ? "none" : "2px solid #00f" ?>;
			border-bottom:<?php echo $masterMaze[$x][$y]['bottom'] ? "none" : "2px solid #00f" ?>;
			border-left:<?php echo $masterMaze[$x][$y]['left'] ? "none" : "2px solid #00f" ?>;">
		</td>
	<?php endfor; ?>
	</tr>
<?php endfor; ?>
</table>