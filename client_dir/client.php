#!/usr/bin/php -q
<?php
error_reporting(E_ALL);
include("includes.php");

if ($argc == 5 || $argc == 7)
{
	$i = 0;
	$tbl = array();
	foreach ($argv as $row)
	{
		if ($row == "-n" && $i > 0)
			$tbl["team"] = $argv[$i + 1];
		if ($row == "-p" && $i > 0)
			$tbl["port"] = $argv[$i + 1];
		if ($row == "-h" && $i > 0)
			$tbl["host"] = $argv[$i + 1];
		$i++;
	}
	if (count($tbl) != 3 && $argc == 7)
		ft_usage();
	if (!isset($tbl["host"]))
		$tbl["host"] = "127.0.0.1";
	if (count($tbl) != 3)
		ft_usage();
	$socket = func_connect($tbl);
	$map = ft_init($socket, $tbl);
	$GLOBALS['inventaire']["team"] = $tbl["team"];
	ft_play($socket, $map, $tbl);
}
else
	ft_usage();
?>