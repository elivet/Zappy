package com.base.game;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;

/**
 * Created by rbenjami on 6/19/14.
 */
public class Server
{
    private SocketChannel channel;
    private int           port;
    private int           mapX = 0;
    private int           mapY = 0;

    private String        oldMsg = "";

    public Server(int port) throws IOException
    {
        this.port = port;
        this.channel = SocketChannel.open();

        // we open this channel in non blocking mode
        this.channel.configureBlocking(false);
        this.channel.connect(new InetSocketAddress("localhost", this.port));

        while (!this.channel.finishConnect())
            ;

        if (!this.channel.isConnected())
        {
            System.out.println("Connexion error");
            System.exit(-1);
        }
    }

    /*
    METHOD
     */
    public String readOnServ()
    {
        ByteBuffer bufferR = ByteBuffer.allocate(128);
        int count = 0;
        String message = oldMsg;
        try
        {
            while (this.channel.isConnected() && (count = this.channel.read(bufferR)) > 0)
            {
                bufferR.flip();
                message += Charset.defaultCharset().decode(bufferR);
                if (message.contains("\n"))
                {
                    String[] tab = message.split("\\n");
                    String save = message;
                    message = tab[0];
                    oldMsg = save.substring(message.length() + 1);
                    System.out.println("DEBUG: gfx received: [" + message + "]");
                    return message + "\n";
                }
                else
                    oldMsg += message;
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        if (message.contains("\n"))
        {
            String[] tab = message.split("\\n");
            String save = message;
            message = tab[0];
            oldMsg = save.substring(message.length() + 1);
            System.out.println("DEBUG: gfx received: [" + message + "]");
            return message + "\n";
        }
        else
            oldMsg += message;
        return null;
    }

    public void writeOnServ(String str)
    {
        CharBuffer bufferW = CharBuffer.wrap(str);
        try
        {
            while (bufferW.hasRemaining())
            {
                this.channel.write(Charset.defaultCharset().encode(bufferW));
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public void close()
    {
        try
        {
            this.channel.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }


    /*
    GETTER
     */
    public int getPort()
    {
        return port;
    }

    public SocketChannel getChannel()
    {
        return channel;
    }

    public int getMapX()
    {
        return mapX;
    }

    public int getMapY()
    {
        return mapY;
    }

    /*
        SETTER
         */
    public void setMapY(int mapY)
    {
        this.mapY = mapY;
    }

    public void setMapX(int mapX)
    {
        this.mapX = mapX;
    }
}