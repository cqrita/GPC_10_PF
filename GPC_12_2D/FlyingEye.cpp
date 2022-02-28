#include "FlyingEye.h"
#include "Engine/Time.h"
#include <string>
#include "Global.h"
#include "FlySlash.h"
void FlyingEye::Start()
{
    {
        skin.Name = "Animation/FlyingEye/Flight";
        skin.Duration = 0.5f;
        skin.Repeatable = true;

        skin.Length = Vector<2>(50, 50) * 4;
    }
    {
        body.Length = Point(40, 40);

        box.Name = "Image/GBB";
        box.Length = Vector<2>(50, 66);
    }
    {
        constSpeed = 400;
        direction = Dir::I;
    }

    {
        maxHealth = 100;
        health = maxHealth;
    }
    {
        bar.Name = "Image/Bar";
        bar.Length = Vector<2>(60, 10);
        bar.Location[0] = skin.Location[0];
        bar.Location[1] = skin.Location[1] - 40;
    }
    {
        progressBar.Name = "Image/ProgressBar";
        float health = this->health / maxHealth;
        progressBar.Length = Vector<2>(60 * health, 10);
        progressBar.Location[0] = skin.Location[0] + (60 * health) / 2 - 30;
        progressBar.Location[1] = skin.Location[1] - 40;
    }
    {
        barBorder.Name = "Image/ProgressBarBorder";
        barBorder.Length = Vector<2>(60, 10);
        barBorder.Location[0] = skin.Location[0];
        barBorder.Location[1] = skin.Location[1] - 40;
    }
    {
        state = 1;
    }
    {
        colDuration = colConst;
        colState = false;
    }

    {
        attackCool = attackSpeed;
        attackCoolFlag = false;
    }
    {
        attackTime = 0.3f;
        attackDuration = attackTime;
        attack = false;
    }
    {
        deathDuration = deathConst;
        deathState = false;
        exp = false;
    }
    {
        attackSound.Name = "Sound/Swoosh";
        attackSound.Start();
    }
    {
        hitSound.Name = "Sound/Hit";
        hitSound.Start();
    }
    {
        deathSound.Name = "Sound/Explosion";
        deathSound.Start();
    }
}

void FlyingEye::Update()
{
    if (health <= 0 && !deathState)
    {
        deathState = true;
        deathSound.Play();
    }
    if (deathState)
    {
        skin.Name = "Animation/FlyingEye/Death";
        skin.Repeatable = false;
    }
    else if (!attack)
    {
        this->move();
        skin.Name = "Animation/FlyingEye/Flight";
    }
    else if (colState)
    {
        this->move();
        skin.Name = "Animation/FlyingEye/Attack";
    }
    else
    {
        skin.Name = "Animation/FlyingEye/Attack";
    }
    if (attackCoolFlag == false && Length(player - skin.Location) < 80 && (!deathState))
    {
        this->createMissile(player[0], player[1]);
        attackCoolFlag = true;
        attack = true;
    }


    if (colState)
    {
        colDuration -= Engine::Time::Get::Delta();
    }
    if (colDuration < 0)
    {
        colDuration = colConst;
        colState = false;
    }

    if (attackCoolFlag)
    {
        attackCool -= Engine::Time::Get::Delta();
    }
    if (attackCool < 0)
    {
        attackCool = attackSpeed;
        attackCoolFlag = false;
    }

    if (attack)
    {
        attackDuration -= Engine::Time::Get::Delta();
    }
    if (attackDuration < 0 && (!deathState))
    {
        attackDuration = attackTime;
        attack = false;
    }

    if (deathState)
    {
        deathDuration -= Engine::Time::Get::Delta();
    }
    if (deathDuration < 0)
    {
        state = 0;
        this->End();
    }

    {
        body.Center.x = skin.Location[0];
        body.Center.y = skin.Location[1];
        box.Location = skin.Location;
    }
    {
        healthText.Location[0] = skin.Location[0] - cam[0] + camWidth + 30;
        healthText.Location[1] = -skin.Location[1] + cam[1] + camHeight + 80;
        auto healthString = std::to_string(health);
        healthText.Text = healthString.c_str();
    }

    {
        skin.Render();
    }
    {
        bar.Location[0] = skin.Location[0];
        bar.Location[1] = skin.Location[1] - 40;
        bar.Render();
    }
    {
        float health = this->health / maxHealth;
        progressBar.Length = Vector<2>(60 * health, 10);
        progressBar.Location[0] = skin.Location[0] + (60 * health) / 2 - 30;
        progressBar.Location[1] = skin.Location[1] - 40;
        progressBar.Render();
    }
    {
        barBorder.Location[0] = skin.Location[0];
        barBorder.Location[1] = skin.Location[1] - 40;
        barBorder.Render();
    }

    for (auto m = missiles.begin(); m != missiles.end() && !missiles.empty();)
    {
        if ((*m)->state == 1)
        {
            (*m)->Update();
            ++m;
        }
        else
        {
            (*m)->End();
            m = missiles.erase(m);
        }
    }
}

void FlyingEye::End()
{
    for (auto m = missiles.begin(); m != missiles.end() && !missiles.empty();)
    {
        (*m)->End();
        m = missiles.erase(m);
    }
    attackSound.End();
    hitSound.End();
    deathSound.End();
    this->~FlyingEye();
}

void FlyingEye::createMissile(float x, float y)
{
    Vector<2> mouse = { x - skin.Location[0],y - skin.Location[1] };
    float angle = atan2f(mouse[1], mouse[0]) * (180.0f / 3.14159265f);

    Vector<2> location = Normalize(mouse) * 30 + skin.Location;
    FlySlash* missile = new FlySlash(angle, location, mouse);
    missiles.push_back(missile);
    missile->Start();
    attackSound.Play();

}
