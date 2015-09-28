package com.base.engine.core;

import com.base.engine.rendering.*;
import com.base.game.Gfx;
import org.lwjgl.opengl.Display;

import static org.lwjgl.opengl.GL11.glViewport;

public class CoreEngine
{
	private boolean         isRunning;
	private Game            game;
	private RenderingEngine renderingEngine;
	private int             width;
	private int             height;
	private double          frameTime;
    private int             port;
    private Gfx             gfx = null;

	public CoreEngine( int width, int height, double framerate, Game game, int port )
	{
        this.port = port;
		this.isRunning = false;
		this.game = game;
		this.width = width;
		this.height = height;
		this.frameTime = 1.0 / framerate;
		game.setEngine( this );
	}

	public void createWindow( String title )
	{
		Window.createWindow( width, height, title );
		this.renderingEngine = new RenderingEngine();
	}

	public void start()
	{
		if ( isRunning )
			return;
        run();
    }

	public void stop()
	{
		if ( !isRunning )
			return;
        if (gfx != null)
            gfx.close();
		isRunning = false;
	}

	protected void reshape( int width, int height )
	{
		glViewport( 0, 0, width, height );
		renderingEngine.getMainCamera().resizeProjection(width, height);
	}

	private void run()
    {
		isRunning = true;

		int frames = 0;
		long frameCounter = 0;

		game.init();

		double lastTime = Time.getTime();
		double unprocessedTime = 0;

		while ( isRunning )
		{
			if ( Display.wasResized() )
			{
				reshape( Display.getWidth(), Display.getHeight() );
			}
			boolean render = false;

			double startTime = Time.getTime();
			double passedTime = startTime - lastTime;
			lastTime = startTime;

			unprocessedTime += passedTime;
			frameCounter += passedTime;

			while ( unprocessedTime > frameTime )
			{
				render = true;

				unprocessedTime -= frameTime;

				if ( Window.isCloseRequested() )
					stop();

				game.input( (float) frameTime );
				Input.update();

				game.update( (float) frameTime );

				if ( frameCounter >= 1.0 )
				{
					System.out.println( frames );
					frames = 0;
					frameCounter = 0;
				}

                //CMD SERVER
                if (gfx == null)
                    gfx = new Gfx(this.port, game);
                gfx.loop();
            }
			if ( render )
			{
				game.render( renderingEngine );
				Window.render();
				frames++;
			}
			else
			{
				try
				{
					Thread.sleep( 1 );
				}
				catch ( InterruptedException e )
				{
					e.printStackTrace();
				}
			}
		}

		cleanUp();
	}

	private void cleanUp()
	{
		Window.dispose();
	}

	public RenderingEngine getRenderingEngine()
	{
		return renderingEngine;
	}
}
