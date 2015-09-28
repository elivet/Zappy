package com.base.game;

import com.base.engine.components.MeshRenderer;
import com.base.engine.core.Game;
import com.base.engine.core.GameObject;
import com.base.engine.core.Quaternion;
import com.base.engine.core.Vector3f;
import com.base.engine.rendering.Material;
import com.base.engine.rendering.Mesh;
import com.base.engine.rendering.Texture;

import java.util.ArrayList;

/**
 * Created by elivet on 6/19/14.
 */

class Res
{
    GameObject render;
    boolean rendered = false;
}

class Square
{
    private Game game;
    ArrayList<Res> listNourriture;
    ArrayList<Res> listLinemate;
    ArrayList<Res> listDeraumere;
    ArrayList<Res> listSibur;
    ArrayList<Res> listMendiane;
    ArrayList<Res> listPhiras;
    ArrayList<Res> listThystame;

    public Square(Game game, int nourriture, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        this.listNourriture = new ArrayList<Res>();
        this.listLinemate = new ArrayList<Res>();
        this.listDeraumere = new ArrayList<Res>();
        this.listSibur = new ArrayList<Res>();
        this.listMendiane = new ArrayList<Res>();
        this.listPhiras = new ArrayList<Res>();
        this.listThystame = new ArrayList<Res>();
        for (int i = 0; i < nourriture; i++)
            this.listNourriture.add(new Res());
        for (int i = 0; i < linemate; i++)
            this.listLinemate.add(new Res());
        for (int i = 0; i < deraumere; i++)
            this.listDeraumere.add(new Res());
        for (int i = 0; i < sibur; i++)
            this.listSibur.add(new Res());
        for (int i = 0; i < mendiane; i++)
            this.listMendiane.add(new Res());
        for (int i = 0; i < phiras; i++)
            this.listPhiras.add(new Res());
        for (int i = 0; i < thystame; i++)
            this.listThystame.add(new Res());
    }

    public void set(Game game, int nourriture, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        for (Res aListNourriture : this.listNourriture)
            game.delObject(aListNourriture.render);
        for (Res aListLinemate : this.listLinemate)
            game.delObject(aListLinemate.render);
        for (Res aListDeraumere : this.listDeraumere)
            game.delObject(aListDeraumere.render);
        for (Res aListSibur : this.listSibur)
            game.delObject(aListSibur.render);
        for (Res aListMendiane : this.listMendiane)
            game.delObject(aListMendiane.render);
        for (Res listPhira : this.listPhiras)
            game.delObject(listPhira.render);
        for (Res aListThystame : this.listThystame)
            game.delObject(aListThystame.render);
        this.listNourriture.clear();
        this.listLinemate.clear();
        this.listDeraumere.clear();
        this.listSibur.clear();
        this.listMendiane.clear();
        this.listPhiras.clear();
        this.listThystame.clear();
        for (int i = 0; i < nourriture; i++)
            this.listNourriture.add(new Res());
        for (int i = 0; i < linemate; i++)
            this.listLinemate.add(new Res());
        for (int i = 0; i < deraumere; i++)
            this.listDeraumere.add(new Res());
        for (int i = 0; i < sibur; i++)
            this.listSibur.add(new Res());
        for (int i = 0; i < mendiane; i++)
            this.listMendiane.add(new Res());
        for (int i = 0; i < phiras; i++)
            this.listPhiras.add(new Res());
        for (int i = 0; i < thystame; i++)
            this.listThystame.add(new Res());
    }

    public ArrayList<Res> getList(int i)
    {
        if (i == 0)
            return this.listNourriture;
        else if (i == 1)
            return this.listLinemate;
        else if (i == 2)
            return this.listDeraumere;
        else if (i == 3)
            return this.listSibur;
        else if (i == 4)
            return this.listMendiane;
        else if (i == 5)
            return this.listPhiras;
        else if (i == 6)
            return this.listThystame;
        return null;
    }
}

public class Map
{
    private int x;
    private int y;
    private int time;
    private Game game;
    private Square[][] resources;
    private Mesh[] mesh;
    private Mesh planeMesh;
    private Mesh playerMesh;
    private Mesh eggesMesh;
    private Material[] material;
    private Material planeMaterial;
    private Material playerMaterial;
    private Material eggesMaterial;
    private ArrayList<String> team;
    private ArrayList<Player> players;
    private ArrayList<Eggs> egges;

    public Map(Game game, int x, int y)
    {
        this.game = game;
        this.x = x;
        this.y = y;
        this.team = new ArrayList<String>();
        this.players = new ArrayList<Player>();
        this.egges = new ArrayList<Eggs>();
        resources = new Square[x][y];
        mesh = new Mesh[7];
        mesh[0] = new Mesh( "Pumpkin.obj" );
        mesh[1] = new Mesh( "cube.obj" );
        mesh[2] = new Mesh( "cube.obj" );
        mesh[3] = new Mesh( "cube.obj" );
        mesh[4] = new Mesh( "cube.obj" );
        mesh[5] = new Mesh( "cube.obj" );
        mesh[6] = new Mesh( "cube.obj" );
        planeMesh = new Mesh( "plane3.obj" );
        playerMesh = new Mesh( "alduin.obj" );
        eggesMesh = new Mesh( "egg.obj" );
        material = new Material[7];
        material[0] = newTex( "red.png");
        material[1] = newTex( "green.png");
        material[2] = newTex( "yellow.png");
        material[3] = newTex( "blue.png");
        material[4] = newTex( "purple.png");
        material[5] = newTex( "orange.png");
        material[6] = newTex( "brown.png");
        planeMaterial = newTex( "case.png");
        playerMaterial = newTex( "alduin.jpg");
        eggesMaterial = newTex( "brown.png" );
        createMap();
    }

    private Material newTex(String tex)
    {
        Material mat = new Material();
        mat.addTexture("diffuse", new Texture(tex));
        mat.addTexture("normalMap", new Texture("default_normal.jpg"));
        mat.addFloat("specularIntensity", 1);
        mat.addFloat("specularPower", 4);
        return mat;
    }

    private void createMap()
    {
        int x = ((float)this.x / 2) > this.x / 2 ? this.x / 2 + 1 : this.x / 2;
        int y = ((float)this.y / 2) > this.y / 2 ? this.y / 2 + 1 : this.y / 2;
        for (int i = -(this.x / 2); i < x; i++)
        {
            for (int j = -y; j < this.y / 2;j++)
            {
                MeshRenderer meshRenderer = new MeshRenderer( planeMesh, planeMaterial );
                GameObject planeObject = new GameObject();
                planeObject.addComponent( meshRenderer );
                planeObject.getTransform().getPos().set( i * 16.09f, 0, j * 16.09f );
                this.game.addObject(planeObject);
            }
        }
    }

    public void updatePlayer()
    {
        for (Player player : players)
        {
            if (!player.isRendered())
            {
                MeshRenderer playerRenderer = new MeshRenderer( playerMesh, material[player.getColor()] );
                GameObject playerObject = new GameObject();
                playerObject.addComponent( playerRenderer );
                playerObject.getTransform().getPos().set((player.getX() - (this.x / 2)) * 16, 5, ((this.y / 2) - player.getY() - 1) * 16);
                playerObject.getTransform().setRot(new Quaternion(new Vector3f(0, 1, 0), (float)Math.toRadians((player.getDir()) * 90)));
                playerObject.getTransform().setScale( 1f, 1f, 1f);
                this.game.addObject(playerObject);
                player.setRender(playerObject);
            }
            else
            {
                player.getRender().getTransform().getPos().set((player.getX() - (this.x / 2)) * 16, 5, ((this.y / 2) - player.getY() - 1) * 16);
                player.getRender().getTransform().setRot(new Quaternion(new Vector3f(0, 1, 0), (float) Math.toRadians((player.getDir()) * 90)));
            }
        }
    }

    public void updateEgges()
    {
        for (Eggs e : egges)
        {
            if (!e.isRendered())
            {
                MeshRenderer playerRenderer = new MeshRenderer( eggesMesh, eggesMaterial );
                GameObject playerObject = new GameObject();
                playerObject.addComponent(playerRenderer);
                playerObject.getTransform().getPos().set((e.getX() - (this.x / 2)) * 16, 1, ((this.y / 2) - e.getY() - 1) * 16);
                playerObject.getTransform().setScale( 3, 3, 3);
                this.game.addObject(playerObject);
                e.setRender(playerObject);
            }
            else
            {
                e.getRender().getTransform().getPos().set((e.getX() - (this.x / 2)) * 16, 1, ((this.y / 2) - e.getY() - 1) * 16);
            }
        }
    }

    public void updateResources()
    {
        int x = ((float)this.x / 2) > this.x / 2 ? this.x / 2 + 1 : this.x / 2;
        int y = ((float)this.y / 2) > this.y / 2 ? this.y / 2 + 1 : this.y / 2;
        for (int i = -(this.y / 2); i < y; i++)
        {
            for (int j = -(this.x / 2); j < x;j++ )
                addResources(j + (this.x / 2), i + (this.y / 2));
        }
    }

    private void addResources(int i, int j)
    {
        for (int k = 0; k < 7; k++)
        {
            int l = 0;
            for (Res res : resources[i][j].getList(k))
            {
                if (!res.rendered)
                {
                    MeshRenderer meshRenderer = new MeshRenderer(mesh[k], material[k]);
                    GameObject planeObject = new GameObject();
                    planeObject.addComponent(meshRenderer);
                    if (k != 0)
                    {
                        planeObject.getTransform().getPos().set((i - this.x / 2) * 16.09f - 6 + l, 0, (this.y / 2 - j - 1) * 16.09f - 6 + k + 2);
                        planeObject.getTransform().setScale(0.1f, 0.1f, 0.1f);
                    }
                    else
                        planeObject.getTransform().getPos().set((i - this.x / 2) * 16.09f - 6 + l, 0, (this.y / 2 - j - 1) * 16.09f - 6 + k);
                    this.game.addObject(planeObject);
                    res.render = planeObject;
                    res.rendered = true;
                    l++;
                    if (l >= 500 / (this.x * this.y))
                        break ;
                }
            }
        }
    }

    public void addTeam(String name)
    {
        team.add(name);
    }

    public void addPlayer(Player player)
    {
        this.players.add(player);
    }

    public void addEgges(Eggs egges)
    {
        this.egges.add(egges);
    }

    /*
    GETER
     */
    public int getX()
    {
        return x;
    }

    public int getY()
    {
        return y;
    }

    public Square[][] getResources()
    {
        return resources;
    }

    public ArrayList<Player> getPlayers()
    {
        return players;
    }

    public Player getPlayer(int nb)
    {
        for (Player player : players)
        {
            if (player.getNb() == nb)
                return player;
        }
        return null;
    }

    public ArrayList<Eggs> getEgges()
    {
        return egges;
    }

    /*
            SETTER
             */
    public void setX(int x)
    {
        this.x = x;
    }

    public void setY(int y)
    {
        this.y = y;
    }

    public void setTime(int time)
    {
        this.time = time;
    }
}