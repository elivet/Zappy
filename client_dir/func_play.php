<?php

function	ft_play($socket, $map, $tbl)
{
	$pos = array("x" => 0, "y" => 0, "d" => 0);
	$lvl = 1;
	$current = 0;
	$i = 0;
	ft_inventaire($socket);
	while (42)
	{
		$tmp = ft_connect_nbr($socket);
		if ($tmp == 0 && $i == 0)
		{
			ft_fork($socket);
			$i++;
		}
		else if ($tmp != 0 && $i < 2)
		{
			ft_dedouble($socket, $tbl);
			$i++;
		}
		if ($current == 0)
			$current = ft_see($socket);
		ft_search($socket, $current, $lvl, "nourriture");
		ft_check_objectif($socket, $lvl, $current);
		if (ft_search_up($socket, $current, $lvl) == TRUE)
			$lvl = ft_incantation($socket, $lvl, $current, TRUE);
		else
			ft_move($socket, $current);
		$current = 0;
	}
}

function ft_check_objectif($socket, $lvl, $current)
{
	foreach ($GLOBALS['stack'] as $key => $value)
	{
		if ($key != "nb_joueur" && $GLOBALS['inventaire'][$key] < $value)
			return ;
	}
	ft_up($socket, $lvl, $current);
}

function ft_up($socket, $lvl, $current)
{
	if (isset($GLOBALS['last_call']) && $GLOBALS['last_call'])
	{
		$movement = array(
						1 => array("avance"),
						2 => array("avance", "gauche", "avance"),
						3 => array("gauche", "avance"),
						4 => array("gauche", "avance", "gauche", "avance"),
						5 => array("droite", "droite", "avance"),
						6 => array("droite", "avance", "droite", "avance"),
						7 => array("droite", "avance"),
						8 => array("avance", "droite", "avance"),
					);
		while ($GLOBALS['last_call'] != 42)
		{
			ft_exec_travel($movement[$GLOBALS['last_call']], $socket);
			$current = ft_see($socket);
			ft_search($socket, $current, $lvl, "nourriture");
			if ($GLOBALS['t_last_call'] > time() + (310 * $GLOBALS["time"]))
				ft_call($socket, $current, $lvl);
		}
		while ($GLOBALS['last_call'] == 42)
		{
			socket_write($socket, "broadcast " . $GLOBALS['inventaire']["team"] . "\n");
			echo "broadcast " . $GLOBALS['inventaire']["team"] . "\n";
			get_next_line_socket($socket, "broadcast");
			if ($GLOBALS['inventaire']["nourriture"] > 20)
			{
				socket_write($socket, "pose nourriture\n");
				echo "pose nourriture\n";
				get_next_line_socket($socket, "pose");
			}
			$current = ft_see($socket);
			$lvl = ft_incantation($socket, $lvl, $current, FALSE);
		}
	}
	else
		ft_call($socket, $current, $lvl);
}

function ft_call($socket, $current, $lvl)
{
	while (42)
	{
		socket_write($socket, "broadcast " . $GLOBALS['inventaire']["team"] . "\n");
		echo "broadcast " . $GLOBALS['inventaire']["team"] . "\n";
		get_next_line_socket($socket, "broadcast");
		$current = ft_see($socket);
		ft_search($socket, $current, $lvl, "nourriture");
		$lvl = ft_incantation($socket, $lvl, $current, FALSE);
	}
}

?>