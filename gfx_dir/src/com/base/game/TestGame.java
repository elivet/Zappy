package com.base.game;

import com.base.engine.components.*;
import com.base.engine.core.*;
import com.base.engine.rendering.*;

public class TestGame extends Game
{
	public void init()
	{
//		Mesh mesh = new Mesh( "plane3.obj" );
//		Material material = new Material();//new Texture("test.png"), new Vector3f(1,1,1), 1, 8);
//		material.addTexture( "diffuse", new Texture( "basic.jpg" ) );
//		material.addTexture( "normalMap", new Texture( "default_normal.jpg" ) );
//		material.addFloat( "specularIntensity", 1 );
//		material.addFloat( "specularPower", 8 );

//		Material material2 = new Material();//new Texture("test.png"), new Vector3f(1,1,1), 1, 8);
//		material2.addTexture( "diffuse", new Texture( "bricks2.jpg" ) );
//		material2.addTexture( "normalMap", new Texture( "bricks2_normal.jpg" ) );
//		material2.addFloat( "specularIntensity", 1 );
//		material2.addFloat( "specularPower", 8 );

//		Mesh tempMesh = new Mesh( "alduin.obj" );

//		MeshRenderer meshRenderer = new MeshRenderer( mesh, material );

//		GameObject planeObject = new GameObject();
//		planeObject.addComponent( meshRenderer );
//		planeObject.getTransform().getPos().set( 0, -1, 5 );

		GameObject directionalLightObject = new GameObject();
		DirectionalLight directionalLight = new DirectionalLight( new Vector3f( 1, 1, 1 ), 0.1f );
		GameObject directionalLightObject2 = new GameObject();
		DirectionalLight directionalLight2 = new DirectionalLight( new Vector3f( 1, 1, 1 ), 0.1f );

		directionalLightObject.addComponent( directionalLight );
		addObject( directionalLightObject );

		directionalLightObject2.addComponent( directionalLight2 );
		addObject( directionalLightObject2 );

		addObject( new GameObject().addComponent( new FreeLook( 0.5f ) ).addComponent( new FreeMove( 20.0f ) ).addComponent( new Camera( (float) Math.toRadians( 70.0f ), (float) Window.getWidth() / (float) Window.getHeight(), 0.01f, 1000.0f ) ) );

		directionalLight.getTransform().setRot( new Quaternion( new Vector3f( 1, 0, 0 ), (float) Math.toRadians( -45 ) ) );
		directionalLight2.getTransform().setRot( new Quaternion( new Vector3f( 1, 0, 0 ), (float) Math.toRadians( -45 ) ) );
		directionalLight2.getTransform().rotate( new Vector3f( 0, 1, 0 ), (float) Math.toRadians( 180 ) );
	}
}
