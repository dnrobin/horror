<?php

define('DIR_NORTH',	0);
define('DIR_SOUTH',	1);
define('DIR_EAST',	2);
define('DIR_WEST', 	3);

$mazeWidth = 32;
$mazeHeight = 32;

$maze = array();


// initialize maze array
for ( $x = 0; $x < $mazeWidth; $x ++ ) {
	for ( $y = 0; $y < $mazeHeight; $y ++ ) {
		$maze[$x][$y] = array(
			'active' => false,
			'branch' => false,
			'wall_north' => false,
			'wall_east' => false,
			'wall_south' => false,
			'wall_west' => false,
		);
	}
}

// randomly generate paths in maze
tracePath( $mazeWidth / 2 + 1, $mazeHeight / 2 + 1, rand(0, 3) );

function tracePath($x, $y, $dir) {
	static $depth = 0; $depth++; $maxDepth = 100;
	if ( $depth > $maxDepth ) return;
	
	global $mazeWidth;
	global $mazeHeight;
	
	global $maze;
	
	$maxPathLength = 10;
	
	// randomly choose a path length
	$len = rand(2, $maxPathLength);
	
	// randomly choose number of possible branch offs
	$branches = rand(1, 3);
	
	echo "Tracing Path (",$depth,") at x:",$x," y:",$y," in direction:",$dir," with max length:",$len," and possible branches:",$branches,"<br/>";
	
	$branching = array();
	
	// set maze array path
	switch ( $dir ) {
		case DIR_NORTH:
			for ( $yy = $y-1; $yy >= $y - $len; $yy -- ) {
				if ( $yy < 0 || $maze[$x][$yy]['active'] ) break;
				$maze[$x][$yy]['active'] = true;
				
				if ( $branches > 0 && rand(0, 1) == 1 ) {
					$branches--;
					$maze[$x][$yy]['branch'] = true;
					$d = rand(2,3);
					$maze[$x][$yy]['wall_west'] = ($d == 2);
					$maze[$x][$yy]['wall_east'] = ($d == 3);
					$branching[] = array('x'=>$x, 'y'=>$yy, 'dir'=>$d);
				} else {
					$maze[$x][$yy]['wall_west'] = true;
					$maze[$x][$yy]['wall_east'] = true;
				}
			}
			$maze[$x][$yy+1]['wall_north'] = true;
		break;
		case DIR_EAST:
			for ( $xx = $x+1; $xx <= $x + $len; $x ++ ) {
				if ( $xx >= $mazeWidth || $maze[$xx][$y]['active'] ) break;
				$maze[$xx][$y]['active'] = true;
				
				if ( $branches > 0 && rand(0, 1) == 1 ) {
					$branches--;
					$maze[$xx][$y]['branch'] = true;
					$d = rand(0,1);
					$maze[$xx][$y]['wall_north'] = ($d == 1);
					$maze[$xx][$y]['wall_south'] = ($d == 0);
					$branching[] = array('x'=>$xx, 'y'=>$y, 'dir'=>$d);
				} else {
					$maze[$xx][$y]['wall_north'] = true;
					$maze[$xx][$y]['wall_south'] = true;
				}
			}
			$maze[$xx-1][$y]['wall_east'] = true;
		break;
		case DIR_SOUTH:
			for ( $yy = $y+1; $yy <= $y + $len; $yy ++ ) {
				if ( $yy >= $mazeHeight || $maze[$x][$yy]['active'] ) break;
				$maze[$x][$yy]['active'] = true;
				$maze[$x][$yy]['wall_west'] = true;
				$maze[$x][$yy]['wall_east'] = true;
				
				if ( $branches > 0 && rand(0, 1) == 1 ) {
					$branches--;
					$maze[$x][$yy]['branch'] = true;
					$d = rand(2,3);
					$maze[$x][$yy]['wall_west'] = ($d == 2);
					$maze[$x][$yy]['wall_east'] = ($d == 3);
					$branching[] = array('x'=>$x, 'y'=>$yy, 'dir'=>$d);
				} else {
					$maze[$x][$yy]['wall_west'] = true;
					$maze[$x][$yy]['wall_east'] = true;
				}
			}
			$maze[$x][$yy-1]['wall_south'] = true;
		break;
		case DIR_WEST:
			for ( $xx = $x-1; $xx >= $x - $len; $x -- ) {
				if ( $xx < 0 || $maze[$xx][$y]['active'] ) break;
				$maze[$xx][$y]['active'] = true;
				$maze[$xx][$y]['wall_north'] = true;
				$maze[$xx][$y]['wall_south'] = true;
				
				if ( $branches > 0 && rand(0, 1) == 1 ) {
					$branches--;
					$maze[$xx][$y]['branch'] = true;
					$d = rand(0,1);
					$maze[$xx][$y]['wall_north'] = ($d == 1);
					$maze[$xx][$y]['wall_south'] = ($d == 0);
					$branching[] = array('x'=>$xx, 'y'=>$y, 'dir'=>$d);
				} else {
					$maze[$xx][$y]['wall_north'] = true;
					$maze[$xx][$y]['wall_south'] = true;
				}
			}
			$maze[$xx+1][$y]['wall_west'] = true;
		break;
	}
	
	foreach( $branching as $b ) {
		tracePath( $b['x'], $b['y'], $b['dir'] );
	}
	
}

?>
<table border="0" style="margin:10% auto; border-collapse:collaps2e;">
<?php for( $y = 0; $y < $mazeHeight; $y ++ ) :?>
	<tr>
	<?php for( $x = 0; $x < $mazeWidth; $x ++ ) :?>
		<td style="
			width:16px;
			height:16px;
			background-color:<?php echo $maze[$x][$y]['branch'] ? "#f6f6f6" : "none" ?>;
			border-top:<?php echo !$maze[$x][$y]['wall_north'] ? "none" : "2px solid #00f" ?>;
			border-right:<?php echo !$maze[$x][$y]['wall_east'] ? "none" : "2px solid #0f0" ?>;
			border-bottom:<?php echo !$maze[$x][$y]['wall_south'] ? "none" : "2px solid #f00" ?>;
			border-left:<?php echo !$maze[$x][$y]['wall_west'] ? "none" : "2px solid #ff0" ?>;">
		</td>
	<?php endfor; ?>
	</tr>
<?php endfor; ?>
</table>