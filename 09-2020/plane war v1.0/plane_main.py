import pygame
import plane_sprites

class PlaneGame(object):
    """PLANE WAR"""

    def __init__(self):
        print("Game initialization...")

        # create window
        self.screen = pygame.display.set_mode(plane_sprites.SCREEN_RECT.size)

        # create clock
        self.clock = pygame.time.Clock()

        # call private method to create sprites and sprites group
        self.__create_sprites()

        # set timer event - create enemy
        pygame.time.set_timer(plane_sprites.CREATE_ENEMY_EVENT, 1000)  # (event, time in ms)

    def __create_sprites(self):
        # background sprite group
        bg1 = plane_sprites.Background()
        bg2 = plane_sprites.Background(True)
        self.back_group = pygame.sprite.Group(bg1, bg2)

        # enemy group
        self.enemy_group = pygame.sprite.Group()

        # hero group
        self.hero = plane_sprites.Hero()
        self.hero_group = pygame.sprite.Group(self.hero)

    def start_game(self):
        print("Game start!!")

        while True:
            # set FPS
            self.clock.tick(plane_sprites.FPS)
            # capture events
            self.__event_handler()
            # check collision
            self.__check_collision()
            # update/draw the sprites
            self.__update_sprites()
            # update the screen
            pygame.display.update()

    def __event_handler(self):
        # quit game
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                PlaneGame.__game_over()
            elif event.type == plane_sprites.CREATE_ENEMY_EVENT:
                # create enemy sprite
                enemy = plane_sprites.Enemy()
                # add enemy to enemy group
                self.enemy_group.add(enemy)

        # get key_press value, get_pressed() return a tuple(sequence of boolean value)
        # if the corresponding key is being pressed, its value is 1, otherwise is 0
        # here speedx is x-co, speed is y-co
        key_pressed = pygame.key.get_pressed()
        if key_pressed:  # if 4 boolean val in the tuple are 0 (user is not pressing), this statement will be executed
            self.hero.speedX = 0
            self.hero.speedY = 0
        if key_pressed[pygame.K_SPACE]:
            self.hero.fire()
        if key_pressed[pygame.K_RIGHT]:
            self.hero.speedX = plane_sprites.HERO_SPEED
        if key_pressed[pygame.K_UP]:
            self.hero.speedY = -plane_sprites.HERO_SPEED
        if key_pressed[pygame.K_LEFT]:
            self.hero.speedX = -plane_sprites.HERO_SPEED
        if key_pressed[pygame.K_DOWN]:
            self.hero.speedY = plane_sprites.HERO_SPEED

    def __check_collision(self):
        # bullet destroy enemy
        pygame.sprite.groupcollide(self.hero.bullet_group, self.enemy_group, True, True)
        # enemy destroy hero, return type = enemy which crashes hero (list)
        enemies = pygame.sprite.spritecollide(self.hero, self.enemy_group, True)
        # if this list has len > 0 , means crashed, game over
        if len(enemies) > 0:
            self.hero.kil()
            PlaneGame.__game_over()

    def __update_sprites(self):
        # 1. update
        # 2. draw the changes in canvas, use blit, ** draw would call blit
        self.back_group.update()
        self.back_group.draw(self.screen)

        self.enemy_group.update()
        self.enemy_group.draw(self.screen)

        self.hero_group.update()
        self.hero_group.draw(self.screen)

        self.hero.bullet_group.update()
        self.hero.bullet_group.draw(self.screen)

    @staticmethod
    def __game_over():
        print("Game over")

        pygame.quit()
        exit()


if __name__ == '__main__':
    # create game object
    game = PlaneGame()

    # start game
    game.start_game()