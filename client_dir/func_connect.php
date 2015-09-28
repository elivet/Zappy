<?php
	function func_connect($tbl)
	{
		if (!($socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)))
			ft_error("socket_create", TRUE);
		if (!socket_connect($socket, $tbl["host"], $tbl["port"]))
			ft_error("socket_connect", TRUE);

		return ($socket);
	}
?>