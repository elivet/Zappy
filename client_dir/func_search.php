<?php

function ft_search($socket, $current, $lvl, $object)
{
	foreach ($current[0] as $data)
	{
		if ($data == $object)
		{
			socket_write($socket, "prend " . $object . "\n");
			echo "prend " . $object . "\n";
			if (($tmp = get_next_line_socket($socket, "prend")) == "ok\n")
				$GLOBALS['inventaire'][$data]++;
			else if ($tmp == "ko\n")
			{
				ft_inventaire($socket);
				return false ;
			}
		}
	}
	ft_inventaire($socket);
	return (true);
}

function ft_search_up($socket, $current, $lvl)
{
	foreach ($current[0] as $data)
	{
		if (isset($GLOBALS['stack'][$data]) && $GLOBALS['stack'][$data] > $GLOBALS['inventaire'][$data])
		{
			socket_write($socket, "prend " . $data . "\n");
			echo "prend " . $data . "\n";
			if (($tmp = get_next_line_socket($socket, "prend")) == "ok\n")
				$GLOBALS['inventaire'][$data]++;
			else if ($tmp == "ko\n")
				return (FALSE);
		}
	}
	foreach ($GLOBALS['leveling'][$lvl - 1] as $key => $value)
	{
		if ($key != "nb_joueur" && $GLOBALS['inventaire'][$key] <= $value)
			return (FALSE);
	}
	return (TRUE);
}
?>