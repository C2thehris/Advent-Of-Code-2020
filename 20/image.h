#include <list>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>

struct Tile
{
    void mirrorY()
    {
        Tile *btemp = borders[2];
        std::string ltemp = lines[2];

        borders[2] = borders[0];
        lines[2] = lines[0];

        borders[0] = btemp;
        lines[0] = ltemp;

        std::reverse(lines[1].begin(), lines[1].end());
        std::reverse(lines[3].begin(), lines[3].end());
        for (std::string &s : grid)
        {
            std::reverse(s.begin(), s.end());
        }
    }

    void mirrorX()
    {
        Tile *btemp = borders[3];
        std::string ltemp = lines[3];

        borders[3] = borders[1];
        lines[3] = lines[1];

        borders[1] = btemp;
        lines[1] = ltemp;

        std::reverse(lines[0].begin(), lines[0].end());
        std::reverse(lines[2].begin(), lines[2].end());
        std::reverse(grid.begin(), grid.end());
    }

    //Rotates 90 degrees Clockwise
    void rotateCW()
    {
        Tile *ttemp1;
        Tile *ttemp2 = borders[3];
        std::string ltemp1;
        std::string ltemp2 = lines[3];
        for (int i = 0; i < 4; ++i)
        {
            ttemp1 = borders[i];
            ltemp1 = lines[i];

            if (i % 2 == 0)
            {
                std::reverse(ltemp1.begin(), ltemp1.end());
            }

            borders[i] = ttemp2;
            lines[i] = ltemp2;

            ttemp2 = ttemp1;
            ltemp2 = ltemp1;
        }

        std::vector<std::string> ngrid;
        for (int i = signed(grid.size()) - 1; i >= 0; --i)
        {
            for (unsigned int j = 0; j < grid[i].size(); ++j)
            {
                if (ngrid.size() <= j)
                {
                    ngrid.push_back({grid[i][j]});
                }
                else
                {
                    ngrid[j].push_back({grid[i][j]});
                }
            }
        }
        grid = ngrid;
    }

    int id;
    std::vector<Tile *> borders = {nullptr, nullptr, nullptr, nullptr}; //[0], left; [1], up; [2], right; [3], down;
    int count = 0;
    std::vector<std::string> grid;
    std::vector<std::string> lines; //[0], left; [1], up; [2], right; [3], down;
};

class Image
{
public:
    Image(Tile &tl)
    {
        while (!tl.borders[3] || !tl.borders[2])
        {
            tl.rotateCW();
        }

        image.push_back({&tl});
        makeRows(tl.borders[3], &tl);
        makeBorderColumn(image[0], tl.borders[2], &tl);

        for (unsigned int i = 1; i < image.size(); ++i)
        {
            gapFill(image[i], i - 1);
        }
    }

    int countMarks(const std::vector<std::string> &grid) const
    {
        int total = 0;
        for (std::string line : grid)
        {
            for (char c : line)
            {
                if (c == '#')
                {
                    ++total;
                }
            }
        }
        return total;
    }

    void rotateCW()
    {
        std::vector<std::vector<Tile *>> nimage;
        for (int i = signed(image.size()) - 1; i >= 0; --i)
        {
            for (unsigned int j = 0; j < image[i].size(); ++j)
            {
                image[i][j]->rotateCW();
                if (nimage.size() <= j)
                {
                    nimage.push_back({image[i][j]});
                }
                else
                {
                    nimage[j].push_back({image[i][j]});
                }
            }
        }
        image = nimage;
    }

    void mirrorX()
    {
        std::reverse(image.begin(), image.end());
        for (auto row : image)
        {
            for (auto t : row)
            {
                t->mirrorX();
            }
        }
    }

    void mirrorY()
    {
        for (auto row : image)
        {
            std::reverse(row.begin(), row.end());
        }
        for (auto row : image)
        {
            for (auto t : row)
            {
                t->mirrorY();
            }
        }
    }

    void findOrientation(Tile *tl, Tile *last, int direction)
    {
        if (direction == 3)
        {
            while (!tl->borders[1] || tl->borders[1]->id != last->id)
            {
                tl->rotateCW();
            }
            if (tl->lines[1] != last->lines[3])
            {
                tl->mirrorY();
            }
        }
        else if (direction == 2)
        {
            while (!tl->borders[0] || tl->borders[0]->id != last->id)
            {
                tl->rotateCW();
            }
            if (tl->lines[0] != last->lines[2])
            {
                tl->mirrorX();
            }
        }
        else if (direction == 1)
        {
            while (!tl->borders[3] || tl->borders[3]->id != last->id)
            {
                tl->rotateCW();
            }
            if (tl->lines[3] != last->lines[1])
            {
                tl->mirrorY();
            }
        }
        else
        {
            while (!tl->borders[2] || tl->borders[2]->id != last->id)
            {
                tl->rotateCW();
            }
            if (tl->lines[2] != last->lines[0])
            {
                tl->mirrorX();
            }
        }
    }

    void makeRows(Tile *tl, Tile *last)
    {
        findOrientation(tl, last, 3);

        if (tl->count == 2)
        {
            image.push_back({tl});
            return;
        }
        image.push_back({tl});
        makeRows(tl->borders[3], tl);
    }

    void makeBorderColumn(std::vector<Tile *> &row, Tile *tl, Tile *last)
    {
        findOrientation(tl, last, 2);

        if (tl->count == 2)
        {
            row.push_back(tl);
            return;
        }

        row.push_back(tl);
        makeBorderColumn(row, tl->borders[2], tl);
    }

    void gapFill(std::vector<Tile *> &row, int above)
    {
        for (unsigned int i = 1; i < image[above].size(); ++i)
        {
            Tile *lneighbor = row[i - 1];
            Tile *uneighbor = image[above][i];

            if (lneighbor->borders[2] != uneighbor->borders[3])
            {
                std::cerr << "Error: mismatch between neighboring squares IDs: "
                          << lneighbor->id << " " << uneighbor->id << "\n";
                printID();
                exit(1);
            }

            Tile *next = lneighbor->borders[2];

            findOrientation(next, row[i - 1], 2);
            findOrientation(next, image[above][i], 3);
            findOrientation(next, row[i - 1], 2);

            row.push_back(next);
        }
    }

    void print()
    {
        for (const std::vector<Tile *> &row : image)
        {
            for (int i = 0; i < 8; ++i)
            {
                for (Tile const *t : row)
                {
                    std::cout << t->grid[i] << "    ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }

    void printNoSpace()
    {
        for (const std::vector<Tile *> &row : image)
        {
            for (int i = 0; i < 8; ++i)
            {
                for (Tile const *t : row)
                {
                    std::cout << t->grid[i];
                }
                std::cout << "\n";
            }
        }
    }

    void printID()
    {
        for (const std::vector<Tile *> &row : image)
        {
            for (Tile const *t : row)
            {
                std::cout << t->id << "    ";
            }
            std::cout << "\n";
        }
    }

    void markMonsters(const std::vector<std::string> &candidates, std::vector<std::string> &monsters) const
    {
        std::regex second("#(.{4}##){3}#");
        std::regex third(".(#.{2}){6}.");

        for (unsigned int i = 0; i < candidates[0].size() - 20; ++i)
        {
            std::string top = candidates[0].substr(i, 20);
            std::string mid = candidates[1].substr(i, 20);
            std::string bottom = candidates[2].substr(i, 20);

            if (top[18] != '#')
                continue;
            else if (!std::regex_match(mid, second))
                continue;
            else if (!std::regex_match(bottom, third))
                continue;
            else
            {
                monsters[monsters.size() - 3][i + 18] = '#';
                monsters[monsters.size() - 2].replace(i, 20, "#....##....##....###");
                monsters[monsters.size() - 1].replace(i, 20, ".#..#..#..#..#..#...");
            }
        }
    }

    int countMonsterSpots() const
    {
        std::vector<std::string> monsters;
        std::string blank;
        for (unsigned int j = 0; j < 8 * image[0].size(); ++j)
        {
            blank.push_back('.');
        }
        std::vector<std::string> candidates{{}, {}, {}};

        for (unsigned int i = 0; i < image.size(); ++i)
        {
            for (unsigned int j = 0; j < image[0][0]->grid.size(); ++j)
            {
                monsters.push_back(blank);
                for (Tile const *t : image[i])
                {
                    candidates[2] += t->grid[j];
                }
                if (!candidates[0].empty() && !candidates[1].empty())
                {
                    markMonsters(candidates, monsters);
                }

                candidates[0] = candidates[1];
                candidates[1] = candidates[2];
                candidates[2].clear();
            }
        }
        return countMarks(monsters);
    }

    int countP() const
    {
        int total = 0;
        for (const std::vector<Tile *> &row : image)
        {
            for (Tile const *t : row)
            {
                total += countMarks(t->grid);
            }
        }
        total -= countMonsterSpots();
        return total;
    }

    ~Image()
    {
        for (auto itr = image.begin(); itr != image.end(); ++itr)
        {
            itr->clear();
        }
    }

private:
    std::vector<std::vector<Tile *>> image;
};
