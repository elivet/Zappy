package com.base.engine.components;

import com.base.engine.core.*;
import com.base.engine.rendering.RenderingEngine;
import com.base.engine.rendering.Window;

public class Camera extends GameComponent
{
	private Matrix4f projection;
	private float    fov;
	private float    aspect;
	private float    zNear;
	private float    zFar;

	public Camera( float fov, float aspect, float zNear, float zFar )
	{
		this.fov = fov;
		this.aspect = aspect;
		this.zNear = zNear;
		this.zFar = zFar;
		this.projection = new Matrix4f().initPerspective( fov, aspect, zNear, zFar );
	}

	public Matrix4f getViewProjection()
	{
		Matrix4f cameraRotation = getTransform().getTransformedRot().conjugate().toRotationMatrix();
		Vector3f cameraPos = getTransform().getTransformedPos().mul( -1 );

		Matrix4f cameraTranslation = new Matrix4f().initTranslation( cameraPos.getX(), cameraPos.getY(), cameraPos.getZ() );

		return projection.mul( cameraRotation.mul( cameraTranslation ) );
	}

	public void resizeProjection( float width, float height )
	{
		this.projection = new Matrix4f().initPerspective( fov, width / height, zNear, zFar );
	}

	@Override
	public void addToEngine( CoreEngine engine )
	{
		engine.getRenderingEngine().addCamera( this );
	}
}
