<?php

function get_next_line_socket($socket, $cmd)
{
	$str = "";
	while (strlen($buff = socket_read($socket, 2048)) == 2048)
		$str = $str . $buff;
	if ($str . $buff == "mort\n")
		die("mort\n");
	$tmp_result = $str . $buff;
	while (strncmp($tmp_result, "message", 7) && strpos(substr($tmp_result, 8), $GLOBALS['inventaire']["team"]))
	{
		echo ($str . $buff);
		$tmp = explode(',', $str . $buff);
		$tmp = explode(' ', $tmp[0]);
		$GLOBALS['last_call'] = ($tmp[1] == 0) ? 42 : $tmp[1];
		$GLOBALS['t_last_call'] = time();
		$str = "";
		while (strlen($buff = socket_read($socket, 2048)) == 2048)
			$str = $str . $buff;
		if ($str . $buff == "mort\n")
			die("mort\n");
		echo ($str . $buff);
	}
	while (!strncmp($str . $buff, "message", 7))
	{
		while (strlen($buff = socket_read($socket, 2048)) == 2048)
			$str = $str . $buff;
	}
	if ($cmd != "incantation" && ($str . $buff == "elevation en cours\n" || !strncmp($str . $buff, "niveau actuel : ", 16)))
	{
		while (strlen($buff = socket_read($socket, 2048)) == 2048)
			$str = $str . $buff;
		echo ($str . $buff);
		if (!strncmp($str . $buff, "niveau actuel : ", 16))
			$tmp_cmd = $str . $buff;
		else
		{
			while (strlen($buff = socket_read($socket, 2048)) == 2048)
				$str = $str . $buff;
			echo ($str . $buff);
			return ($str = $str . $buff);
		}
		echo ($str . $buff);
		return ($tmp_cmd);
	}
	echo ($str . $buff);
	return ($str . $buff);
}

?>