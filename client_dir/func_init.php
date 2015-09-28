<?php

function ft_init($socket, $tbl)
{
	$out = socket_read($socket, 2048);
	echo $out;

	socket_write($socket, $tbl["team"] . "\n");
	$out = socket_read($socket, 2048);
	echo $out;
	$tbl = explode("\n", $out);
	if ($tbl[1])
	{
		$result = array();
		$tbl2= explode(' ', $tbl[1]);
		$result['x'] = $tbl2[0];
		$result['y'] = $tbl2[1];
		$map = array();
		for ($y = 0; $y < $result['y']; $y++)
		{
			$map[$y] = array();
			for ($x = 0; $x < $result['x']; $x++)
				$map[$y][$x] = 0;
		}
		$map["size"] = $result;
		return ($map);
	}
	ft_error("init map", TRUE);
}

?>