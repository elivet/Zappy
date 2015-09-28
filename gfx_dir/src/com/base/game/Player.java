package com.base.game;

import com.base.engine.core.GameObject;

/**
 * Created by rbenjami on 6/21/14.
 */
public class Player
{
    private int nb;
    private int x;
    private int y;
    private int dir;
    private int level;
    private String team;
    private GameObject render;
    private int color;

    public Player(int nb, int x, int y, int dir, int level, String team, int color)
    {
        this.nb = nb;
        this.x = x;
        this.y = y;
        this.dir = dir;
        this.level = level;
        this.team = team;
        this.render = null;
        this.color = color;
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

    public int getDir()
    {
        return dir;
    }

    public void setDir(int dir)
    {
        this.dir = dir;
    }

    public int getLevel()
    {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public String getTeam()
    {
        return team;
    }

    public void setTeam(String team)
    {
        this.team = team;
    }

    public int getColor()
    {
        return color;
    }
}