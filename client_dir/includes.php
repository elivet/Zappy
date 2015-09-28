<?php

include("func_error.php");
include("func_connect.php");
include("func_gnl.php");
include("func_init.php");
include("func_play.php");
include("func_action.php");
include("func_search.php");
include("func_tools.php");

$GLOBALS['inventaire'] = array();

$GLOBALS['leveling'] = array
	(
		array(
			"nb_joueur" => 1,
			"linemate" => 1
		),
		array(
			"nb_joueur" => 2,
			"linemate" => 1,
			"deraumere" => 1,
			"sibur" => 1
		),
		array(
			"nb_joueur" => 2,
			"linemate" => 2,
			"phiras" => 2,
			"sibur" => 1
		),
		array(
			"nb_joueur" => 4,
			"linemate" => 1,
			"deraumere" => 1,
			"phiras" => 1,
			"sibur" => 2,
		),
		array(
			"nb_joueur" => 4,
			"linemate" => 1,
			"deraumere" => 2,
			"mendiane" => 3,
			"sibur" => 1,
		),
		array(
			"nb_joueur" => 6,
			"linemate" => 1,
			"deraumere" => 2,
			"phiras" => 1,
			"sibur" => 3,
		),
		array(
			"nb_joueur" => 6,
			"linemate" => 2,
			"deraumere" => 2,
			"mendiane" => 2,
			"phiras" => 2,
			"sibur" => 2,
			"thystame" => 1
		),
	);

$GLOBALS['stack'] =
		array(
			"linemate" => 9,
			"deraumere" => 8,
			"mendiane" => 5,
			"phiras" => 6,
			"sibur" => 10,
			"thystame" => 1
		);
?>