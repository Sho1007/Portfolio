#include "Framework.h"
#include "Brick.h"

Brick::Brick(Vector2 pos, Vector2 size, int hp)
    : hp(hp)
{
    center = pos;
    this->size = size;
}

Brick::~Brick()
{
}

void Brick::Render(HDC hdc)
{
    if (hp <= 0)
        return;

    SelectObject(hdc, brushes[hp - 1]);
    Rect::Render(hdc);
}

Direction Brick::Collision(Circle* circle)
{
    if (hp <= 0)
        return Direction::NONE;

    if (IsCircleCollision(circle))
    {
        hp--;

        Vector2 dir = circle->center - center;

        Vector2 leftTop = Vector2(Left(), Top()) - center;
        Vector2 rightTop = Vector2(Right(), Top()) - center;

        if (dir.Cross(leftTop) * dir.Cross(rightTop) < 0)//상하 충돌
        {
            if (center.y > circle->center.y)
            {
                return Direction::UP;
            }
            else
            {
                return Direction::DOWN;
            }
        }
        else//좌우 충돌
        {
            if (center.x > circle->center.x)
            {
                return Direction::LEFT;
            }
            else
            {
                return Direction::RIGHT;
            }
        }
    }

    return Direction::NONE;
}

bool Brick::Collision(Ball* ball)
{
    if (hp <= 0)
        return false;

    if (!IsCircleCollision(ball))
        return false;

    hp--;

    if ((ball->center.x > Left() && ball->center.x < Right()) ||
        (ball->center.y > Top() && ball->center.y < Bottom()))
    {
        Vector2 dir = ball->center - center;

        Vector2 leftTop = Vector2(Left(), Top()) - center;
        Vector2 rightTop = Vector2(Right(), Top()) - center;

        if (dir.Cross(leftTop) * dir.Cross(rightTop) < 0)
        {
            ball->GetDirection()->y *= -1;

            if (ball->center.y < center.y)
                ball->center.y = Top() - ball->radius;
            else
                ball->center.y = Bottom() + ball->radius;
        }
        else
        {
            ball->GetDirection()->x *= -1;    

            if (ball->center.x < center.x)
                ball->center.x = Left() - ball->radius;
            else
                ball->center.x = Right() + ball->radius;
        }        
    }
    else//대각선
    {
        Vector2 dir = (ball->center - center).Normal();
        ball->GetDirection()->x = dir.x;
        ball->GetDirection()->y = dir.y;

        if (dir.x > 0)
        {
            ball->center.x = Right() + ball->radius;            
        }
        else
        {
            ball->center.x = Left() - ball->radius;
        }

        if (dir.y > 0)
        {
            ball->center.y = Bottom() + ball->radius;
        }
        else
        {
            ball->center.y = Top() - ball->radius;
        }
    }

    return true;
}
