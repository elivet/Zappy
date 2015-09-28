<?php

function ft_see($socket)
{
	$timing = time() + microtime();
	socket_write($socket, "voir\n");
	echo "voir\n";
	$result = get_next_line_socket($socket, "voir");
	$GLOBALS["time"] = ((time() + microtime()) - $timing) / 7;
	$result = substr($result, 1, strlen($result) - 3);
	$case = explode(", ", $result);

	foreach ($case as $data)
		$tmp[] = explode(' ', $data);
	foreach ($tmp as $data)
		$current[] = $data;

	return ($current);
}

function ft_connect_nbr($socket)
{
	socket_write($socket, "connect_nbr\n");
	echo "connect_nbr\n";

	return (get_next_line_socket($socket, "connect_nbr"));
}

function ft_fork($socket)
{
	socket_write($socket, "fork\n");

	get_next_line_socket($socket);
}

function ft_inventaire($socket)
{
	socket_write($socket, "inventaire\n");
	echo "inventaire\n";
	$result = get_next_line_socket($socket, "inventaire");
	$result = substr($result, 1, strlen($result) - 3);

	$case = explode(", ", $result);

	print_r($case);
	foreach ($case as $data)
	{
		$data = explode(' ', $data);
		print_r($data);
		$GLOBALS['inventaire'][$data[0]] = $data[1];
	}
}

function ft_incantation($socket, $lvl, $current, $move)
{
	ft_inventaire($socket);
	echo "lvl : " . $lvl . "\n";
	$nb_joueur = 0;
	foreach ($current as $data)
	{
		foreach ($data as $obj)
		{
			if ($obj == "joueur")
				$nb_joueur++;
		}
	}
	if ($GLOBALS['leveling'][$lvl - 1]["nb_joueur"] <= $nb_joueur)
	{
		ft_pose($socket, $lvl);
		socket_write($socket, "incantation\n");
		echo "incantation\n";
		$tmp = get_next_line_socket($socket, "incantation");
		if ($tmp != "ko\n")
		{
			get_next_line_socket($socket, "incantation");
			foreach ($GLOBALS['leveling'][$lvl - 1] as $key => $value)
			{
				if (isset($GLOBALS['stack'][$key]))
				{
					$GLOBALS['stack'][$key] -= $value;
				}
			}
			return ($lvl + 1);
		}
	}
	if ($move)
		ft_move($socket, $current);
	return ($lvl);
}

function ft_pose($socket, $lvl)
{
	foreach ($GLOBALS['leveling'][$lvl - 1] as $key => $value)
	{
		if ($key != "nb_joueur")
		{
			for ($i = 0; $i <= $value; $i++)
			{
				socket_write($socket, "pose " . $key . "\n");
				echo "pose " . $key . "\n";
				if (get_next_line_socket($socket, "pose") == "ok\n")
					$GLOBALS['inventaire'][$key]--;
				else
					return ;
			}
		}
	}
}

function ft_move($socket, $current)
{
	$default_view = ft_create_dv();

	$i = 0;
	$destination = array();
	foreach ($current as $case)
	{
		$destination[$i] = 0;
		foreach ($case as $data)
		{
			if (isset($GLOBALS['stack'][$data]) && $GLOBALS['stack'][$data] > $GLOBALS['inventaire'][$data])
				$destination[$i]++;
		}
		$i++;
	}
	if (max($destination) == 0)
	{
		socket_write($socket, "avance\n");
		echo "avance\n";
		get_next_line_socket($socket, "avance");
		return ;
	}
	$dest = array_search(max($destination), $destination);
	$travel = array();
	foreach ($default_view as $y => $value)
	{
		foreach ($value as $x => $case)
		{
			if ($case == $dest)
			{
				$travel = ft_create_travel($x, $y);
				if (isset($travel[0]))
					ft_exec_travel($travel, $socket);
				return;
			}
		}
	}
}

function ft_dedouble($socket, $tbl)
{
	$cmd = "php client.php -p ". $tbl["port"] . " -n ". $tbl["team"] ." -h ". $tbl["host"] ."> /dev/null 2>/dev/null &";
	exec($cmd);
}
?>