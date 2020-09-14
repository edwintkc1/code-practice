import pygame
import plane_sprites

class PlaneGame(object):
    """PLANE WAR"""

    def __init__(self):
        print("Initialization....")

    def start_game(self):
        print("Game start!")



if __name__ == '__main__':

pygame.init()

# create a canvas of a suitable size
canvas = (480, 700)
screen = pygame.display.set_mode(canvas)  # ((size=(0, 0), flags=0, depth=0, display=0))

"""
create background
1. load image
2. use screen.blit() to put image on canvas
3. update the window
"""
background = pygame.image.load("./images/background.png")
screen.blit(background, (0, 0))


# create player's plane, steps same as above
userPlane = pygame.image.load("./images/me1.png")
userPlane_origin = (180, 500)
screen.blit(userPlane, userPlane_origin)
pygame.display.update()

# create clock object
clock = pygame.time.Clock()

# create a Rect var to record original coordinate of user's plane
userPlane_rect = pygame.Rect(180, 500, 102, 126)  # (x, y, width, height)

# create sprites
enemy = plane_sprites.GameSprite("./images/enemy1.png")

# create sprites group
enemy_group = pygame.sprite.Group(enemy)

# start the game!!
while True:
    # 1. set frame per sec, if tick(1), means 1 frame/s
    clock.tick(60)

    # capture event ***important
    for event in pygame.event.get():  # event.get() return a event list
        if event.type == pygame.QUIT:  # p.s. all events are object, so could call var .type
            print("Exit...")

            pygame.quit()  # unload all modules in pygame
            exit()

    # 2. change user's plane location
    userPlane_rect.y -= 3
    # 2.1 if the plane y's co is above canvas, reset its y co to the bottom of the canvas
    if userPlane_rect.y <= -126:  # 126 is the plane's height, 700 is the bottom of canvas
        userPlane_rect.y = 700

    # 3. draw the changes in canvas, use blit
    screen.blit(background, (0, 0))
    screen.blit(userPlane, userPlane_rect)  # blit(object, new coordinate)

    # TODO
    # Let all sprites in sprite group update their location
    enemy_group.update()
    # draw the changes in canvas, use blit, ** draw would call blit
    enemy_group.draw(screen)

    # 4. update the screen (canvas)
    pygame.display.update()

pygame.quit()