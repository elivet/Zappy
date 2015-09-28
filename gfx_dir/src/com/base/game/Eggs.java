package com.base.game;

import com.base.engine.core.GameObject;

/**
 * Created by rbenjami on 6/25/14.
 */
public class Eggs
{
    private int nb;
    private int x;
    private int y;
    private GameObject render;

    public Eggs(int x, int y, int nb)
    {
        this.x = x;
        this.y = y;
        this.nb = nb;
        this.render = null;
    }

    public Boolean isRendered()
    {
        return render != null;
    }

    public void setRender(GameObject render)
    {
        this.render = render;
    }

    public GameObject getRender()
    {
        return render;
    }

    public int getNb()
    {
        return nb;
    }

    public void setNb(int nb)
    {
        this.nb = nb;
    }

    public int getX()
    {
        return x;
    }

    public void setX(int x)
    {
        this.x = x;
    }

    public int getY()
    {
        return y;
    }

    public void setY(int y)
    {
        this.y = y;
    }

}
