#include "Framework.h"
#include "ShellManager.h"

ShellManager::ShellManager()
{
	for (int i = 0; i < POOL_COUNT; i++)
	{
		shells.emplace_back(new Shell());
	}
}

ShellManager::~ShellManager()
{
	for (Shell* shell : shells)
		delete shell;
}

void ShellManager::Update()
{
	for (Shell* shell : shells)
		shell->Update();
}

void ShellManager::Render(HDC hdc)
{
	for (Shell* shell : shells)
		shell->Render(hdc);
}

void ShellManager::Fire(Vector2 pos, float angle, float speed)
{
	for (Shell* shell : shells)
	{
		if (!shell->IsFire())
		{
			shell->Fire(pos, angle, speed);
			return;
		}
	}
}

bool ShellManager::IsCollision(Object* object)
{
	for (Shell* shell : shells)
	{
		if (shell->IsFire() && object->isActive)
		{
			if (shell->GetBall()->IsCollision(object))
			{
				shell->SetFire(false);
				return true;
			}					
		}
	}

	return false;
}
