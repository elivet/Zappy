package com.base.game;

import com.base.engine.core.CoreEngine;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;

public class Main
{
    public static void main(String[] args) throws IOException
    {
		CoreEngine engine = new CoreEngine( 800, 600, 60, new TestGame(), Integer.valueOf(args[0]) );
		engine.createWindow( "Zappy" );
		engine.start();
    }
}