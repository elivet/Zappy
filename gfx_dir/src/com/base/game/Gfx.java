package com.base.game;

import com.base.engine.core.Game;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by rbenjami on 6/19/14.
 */
public class Gfx
{
    private Game         game;
    private Map          map;
    private Server       serv = null;

    public Gfx(int port, Game game)
    {
        this.game = game;
        try
        {
            this.serv = new Server(port);
            initLoop();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        if (serv == null)
            System.exit(-1);
    }

    private void initLoop() throws IOException
    {
        Matcher m;
        String s;
        while ((s = serv.readOnServ()) == null)
            ;
        if (s.equals("BIENVENUE\n"))
        {
            serv.writeOnServ("GRAPHIC\n");
            while (true)
            {
                if ((s = serv.readOnServ()) != null)
                {
                    if ((m = find(s, Pattern.compile("^msz ([0-9]*) ([0-9]*)\\n$"))) != null)
                        msg(m);
                    if ((m = find(s, Pattern.compile("^sgt ([0-9]*)\\n$"))) != null)
                    {
                        sgt(m);
                        break ;
                    }
                }
            }
        }
    }

    private Matcher find(String s, Pattern p)
    {
        Matcher m;
        m = p.matcher(s);
        if (m.find())
            return m;
        return null;
    }

    private void msg(Matcher m)
    {
        map = new Map(game, Integer.parseInt(m.group(1)), Integer.parseInt(m.group(2)));
    }

    private void sgt(Matcher m)
    {
        map.setTime(Integer.parseInt(m.group(1)));
    }

    private void bct(Matcher m)
    {
        if (map.getResources()[Integer.parseInt(m.group(1))][Integer.parseInt(m.group(2))] == null)
        {
            map.getResources()[Integer.parseInt(m.group(1))][Integer.parseInt(m.group(2))] =
                    new Square(game,
                            Integer.parseInt(m.group(3)),
                            Integer.parseInt(m.group(4)),
                            Integer.parseInt(m.group(5)),
                            Integer.parseInt(m.group(6)),
                            Integer.parseInt(m.group(7)),
                            Integer.parseInt(m.group(8)),
                            Integer.parseInt(m.group(9)));
        }
        else
            map.getResources()[Integer.parseInt(m.group(1))][Integer.parseInt(m.group(2))].set(game,
                    Integer.parseInt(m.group(3)),
                    Integer.parseInt(m.group(4)),
                    Integer.parseInt(m.group(5)),
                    Integer.parseInt(m.group(6)),
                    Integer.parseInt(m.group(7)),
                    Integer.parseInt(m.group(8)),
                    Integer.parseInt(m.group(9)));
        if (map.getResources()[map.getX() - 1][map.getY() - 1] != null)
            map.updateResources();
    }

    int color = 0;
    HashMap<String, Integer> teamList = new HashMap<String, Integer>();
    private int getColor(String str)
    {
        int res;
        if (teamList.containsKey(str))
            res = teamList.get(str);
        else
        {
            teamList.put(str, color);
            res = color;
            color = (color + 1 == 6) ? 0 : color + 1;
        }
        return res;
    }

    private void pnw(Matcher m)
    {
        int color = getColor(m.group(6));
        Player player =
                new Player(
                        Integer.parseInt(m.group(1)),
                        Integer.parseInt(m.group(2)),
                        Integer.parseInt(m.group(3)),
                        Integer.parseInt(m.group(4)),
                        Integer.parseInt(m.group(5)),
                        m.group(6), color);
        map.addPlayer(player);
        map.updatePlayer();
    }

    private void tna(Matcher m)
    {
        map.addTeam(m.group(1));
    }

    private void ppo(Matcher m)
    {
        for (Player player : map.getPlayers())
        {
            if (player.getNb() == Integer.parseInt(m.group(1)))
            {
                player.setX(Integer.parseInt(m.group(2)));
                player.setY(Integer.parseInt(m.group(3)));
                player.setDir(Integer.parseInt(m.group(4)));
            }
        }
        map.updatePlayer();
    }

    private void pgt(Matcher m)
    {
        int x = map.getPlayer(Integer.parseInt(m.group(1))).getX();
        int y = map.getPlayer(Integer.parseInt(m.group(1))).getY();
        if (map.getResources()[x][y].getList(Integer.parseInt(m.group(2))).size() - 1 > 0)
        {
            game.delObject(map.getResources()[x][y].getList(Integer.parseInt(m.group(2))).get(map.getResources()[x][y].getList(Integer.parseInt(m.group(2))).size() - 1).render);
            map.getResources()[x][y].getList(Integer.parseInt(m.group(2))).remove(map.getResources()[x][y].getList(Integer.parseInt(m.group(2))).size() - 1);
            map.updateResources();
        }
    }

    private void pdr(Matcher m)
    {
        int x = map.getPlayer(Integer.parseInt(m.group(1))).getX();
        int y = map.getPlayer(Integer.parseInt(m.group(1))).getY();
        map.getResources()[x][y].getList(Integer.parseInt(m.group(2))).add(new Res());
//        map.getResources()[x][y].set(Integer.parseInt(m.group(2)), map.getResources()[x][y].get(Integer.parseInt(m.group(2))) + 1);
        map.updateResources();
    }

    private void pdi(Matcher m)
    {
        for (Player player : map.getPlayers())
        {
            if (player.getNb() == Integer.parseInt(m.group(1)))
            {
                game.delObject(player.getRender());
                map.getPlayers().remove(player);
                break ;
            }
        }
        map.updatePlayer();
    }

    private void pfk(Matcher m)
    {

    }

    private void enw(Matcher m)
    {
        Eggs egges = new Eggs(Integer.parseInt(m.group(3)), Integer.parseInt(m.group(4)), Integer.parseInt(m.group(1)));
        map.addEgges(egges);
        map.updateEgges();
    }

    private void eht(Matcher m)
    {
        for (Eggs eggs : map.getEgges())
        {
            if (eggs.getNb() == Integer.parseInt(m.group(1)))
            {
                game.delObject(eggs.getRender());
                map.getEgges().remove(eggs);
                break;
            }
        }
    }

    public void loop()
    {
        Matcher m;
        String s;
        if ((s = serv.readOnServ()) != null)
        {
            if ((m = find(s, Pattern.compile("^bct ([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*)\\n$"))) != null)
                bct(m);
            if ((m = find(s, Pattern.compile("^tna ([[a-z]|[A-Z]]*)\\n$"))) != null)
                tna(m);
            if ((m = find(s, Pattern.compile("^pnw #([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*) ([[a-z]|[A-Z]]*)\\n$"))) != null)
                pnw(m);
            if ((m = find(s, Pattern.compile("^ppo #([0-9]*) ([0-9]*) ([0-9]*) ([0-9]*)\\n$"))) != null)
                ppo(m);
            if ((m = find(s, Pattern.compile("^pgt #([0-9]*) ([0-9]*)\\n$"))) != null)
                pgt(m);
            if ((m = find(s, Pattern.compile("^pdr #([0-9]*) ([0-9]*)\\n$"))) != null)
                pdr(m);
            if ((m = find(s, Pattern.compile("^pdi #([0-9]*)\\n$"))) != null)
                pdi(m);
            if ((m = find(s, Pattern.compile("^pfk #([0-9]*)\\n$"))) != null)
                pfk(m);
            if ((m = find(s, Pattern.compile("^enw #([0-9]*) #([0-9]*) ([0-9]*) ([0-9]*)\\n$"))) != null)
                enw(m);
            if ((m = find(s, Pattern.compile("^eht #([0-9]*)\\n$"))) != null)
                eht(m);
        }
    }

    public void close()
    {
        this.serv.close();
    }
}