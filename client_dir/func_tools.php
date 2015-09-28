<?php

function ft_create_dv()
{
	$y = 0;
	$x = 0;
	$tbl = array();
	$max = 1;
	for ($i = 0; $i < 81; $i++)
	{
		$tbl[$y][$x] = $i;
		if ($i == $max * $max - 1)
		{
			$x = $max * (-1);
			$y++;
			$max++;
		}
		else
			$x++;
	}
	return ($tbl);
}

function ft_create_travel($x, $y)
{
	$travel = array();

	if ($x < 0)
	{
		$travel[] = "gauche";
		for ($i = 0; $i < abs($x); $i++)
			$travel[] = "avance";
		$travel[] = "droite";
	}
	else if ($x > 0)
	{
		$travel[] = "droite";
		for ($i = 0; $i < abs($x); $i++)
			$travel[] = "avance";
		$travel[] = "gauche";
	}
	for ($i = 0; $i < $y; $i++)
		$travel[] = "avance";

	return ($travel);
}

function ft_exec_travel($travel, $socket)
{
	foreach ($travel as $data)
	{
		socket_write($socket, $data . "\n");
		echo $data . "\n";
		get_next_line_socket($socket, $data);
	}
}

?>