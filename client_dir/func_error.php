<?php 
	function ft_usage()
	{
		echo "Usage: ./client -n <team> -p <port> [-h <hostname>]\n";
		echo "-n nom d'equipe\n";
		echo "-p port\n";
		echo "-h nom de la machine par defaut c'est le localhost\n";
		exit(0);
	}

	function ft_error($subject, $exit = FALSE)
	{
		echo "An error was occured -- Subject: " . $subject . PHP_EOL;
		if ($exit)
			exit(-1);
	}
?>