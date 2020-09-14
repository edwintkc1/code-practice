import random
import pygame

# screen size constant
SCREEN_RECT = pygame.Rect(0, 0, 480, 700)  # (x, y, width, height)
# frame per second
FPS = 60
# enemy plane 's timer event
CREATE_ENEMY_EVENT = pygame.USEREVENT
# hero's speed
HERO_SPEED = 5


class GameSprite(pygame.sprite.Sprite):  # the first sprite is module, second is class
    """plane war sprite"""

    # constructor
    def __init__(self, image_name, speed=1):
        # if the class is not inherited from object (the default father)
        # we need to use super()__init() first, super is an object
        # then call the father's constructor
        super().__init__()

        self.image = pygame.image.load(image_name)
        self.rect = self.image.get_rect()
        self.speed = speed

    # update the canvas
    def update(self):
        self.rect.y += self.speed  # update y co by certain speed


# We need 2 background keep scrolling, therefore the GameSprite.update() method is not enough
# rewrite the update() method in derived class
class Background(GameSprite):
    """Background sprite"""

    def __init__(self, is_alt=False):  # alt = alternative background, when true, do something
        # set the bg
        super().__init__("./images/background.png")
        # if alt the True, means it is alternative bg, initiate its y co to above the screen
        if is_alt:
            self.rect.y = - self.rect.height

    # make it scrolling
    def update(self):
        super().update()
        # if the bottom background is out of window, move it above the window
        if self.rect.y >= SCREEN_RECT.height:
            self.rect.y = - self.rect.y


class Enemy(GameSprite):
    """Enemy sprite"""

    def __init__(self):
        # create enemy and set its png
        super().__init__("./images/enemy1.png")

        # set its speed, random speed 1-3
        self.speed = random.randint(3, 5)

        # set its born place (x-co and y-co)
        self.rect.bottom = 0
        max_x = SCREEN_RECT.width - self.rect.width
        self.rect.x = random.randint(0, max_x)

    def update(self):
        # keep the enemy flying
        super().update()

        # if enemy fly out of screen (y-co), delete it
        if self.rect.y >= SCREEN_RECT.height:
            self.kill()  # kill() move sprite out of sprite group and delete it


class Hero(GameSprite):
    """User's plane"""

    def __init__(self):
        # set image and speed
        super().__init__("./images/me1.png", 0)
        self.speedX = 0
        self.speedY = 0
        # born place
        self.rect.centerx = SCREEN_RECT.centerx  # set it in the middle (x-co)
        self.rect.bottom = SCREEN_RECT.bottom - 120  # set y-co
        # bullet sprites group
        self.bullet_group = pygame.sprite.Group()

    def update(self):
        # move
        self.rect.x += self.speedX
        self.rect.y += self.speedY  # speed = speed y
        # constrain hero's coordinate
        if self.rect.left < SCREEN_RECT.left:
            self.rect.left = SCREEN_RECT.left
        elif self.rect.right > SCREEN_RECT.right:
            self.rect.right = SCREEN_RECT.right
        if self.rect.top < SCREEN_RECT.top:
            self.rect.top = SCREEN_RECT.top
        elif self.rect.bottom > SCREEN_RECT.bottom:
            self.rect.bottom = SCREEN_RECT.bottom

    def fire(self):
        bullet = Bullet()
        # set coordinate
        bullet.rect.bottom = self.rect.y - 10  # bullet above hero
        bullet.rect.centerx = self.rect.centerx
        # put sprite into bullet sprites group
        self.bullet_group.add(bullet)


class Bullet(GameSprite):
    """Bullet sprite"""

    def __init__(self):
        # set image and original speed
        super().__init__("./images/bullet1.png", -3)

    def update(self):
        super().update()
        # if out of screen, delete it
        if self.rect.bottom < 0:
            self.kill()
