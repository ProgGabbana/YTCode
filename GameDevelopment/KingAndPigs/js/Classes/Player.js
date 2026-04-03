class Player extends Sprite {
    constructor({collisionBlocks = [], imageSrc, frameRate, animations, loop}) {
        super({imageSrc, frameRate, animations, loop})
        this.position = {
            x: 200,
            y: 200,
        }

        this.velocity = {
            x: 0,
            y: 0,
        }

        this.sides = {
            bottom: this.position.y + this.height,
        }
        this.gravity = 1

        this.collisionBlocks = collisionBlocks
    }

    update() {
        // Blue rectangle for testing collisions
        //context.fillStyle = "rgba(0, 0, 255, 0.5)"
        //context.fillRect(this.position.x, this.position.y, this.width, this.height)
        
        this.position.x += this.velocity.x

        // hitbox
        this.updateHitbox()

        // check for horizontal collisions
        this.checkForHorizontalCollisions()

        // apply gravity
        this.applyGravity()

        // hitbox
        this.updateHitbox()

        // Red rectangle for testing
        //context.fillRect(this.hitbox.position.x, this.hitbox.position.y, this.hitbox.width, this.hitbox.height)

        // check for vertical collisions
        this.checkForVerticalCollisions()
    }

    handleInput(keys) {
        if (player.preventInput) return
        player.velocity.x = 0
        if (keys.d.pressed) {
            player.switchSprite('runRight')
            player.velocity.x = 5
            player.lastDirection = 'right'
        } else if (keys.a.pressed) {
            player.switchSprite('runLeft')
            player.velocity.x = -5
            player.lastDirection = 'left'
        }else {
            if (player.lastDirection === 'left') player.switchSprite('idleLeft')
            else player.switchSprite('idleRight')
        }
    }

    switchSprite(name) {
        if (this.image === this.animations[name].image) return
        this.currentFrame = 0
        this.image = this.animations[name].image
        this.frameRate = this.animations[name].frameRate
        this.frameBuffer = this.animations[name].frameBuffer
        this.loop = this.animations[name].loop
        this.currentAnimation = this.animations[name]
    }

    updateHitbox() {
        this.hitbox = {
            position: {
                x: this.position.x + 58,
                y: this.position.y + 34,
            },
            width: 50,
            height: 53,
        }
    }

    checkForHorizontalCollisions() {
        for (let i = 0; i < this.collisionBlocks.length; i++) {
            const collisionBlock = this.collisionBlocks[i]
            // if the player is colliding with a collision block
            if (this.hitbox.position.x <= collisionBlock.position.x + collisionBlock.width && 
                this.hitbox.position.x + this.hitbox.width >= collisionBlock.position.x && 
                this.hitbox.position.y + this.hitbox.height >= collisionBlock.position.y &&
                this.hitbox.position.y <= collisionBlock.position.y + collisionBlock.height
            ) {
                // collision on the left
                if (this.velocity.x < 0) {
                    const offset = this.hitbox.position.x - this.position.x
                    this.position.x = collisionBlock.position.x + collisionBlock.width - offset + 0.01
                    break
                }

                if (this.velocity.x > 0) {
                    const offset = this.hitbox.position.x - this.position.x + this.hitbox.width
                    this.position.x = collisionBlock.position.x - offset - 0.01
                    break
                }
            }   
        }
    }

    applyGravity() {
        this.velocity.y += this.gravity
        this.position.y += this.velocity.y
    }

    checkForVerticalCollisions() {
        for (let i = 0; i < this.collisionBlocks.length; i++) {
            const collisionBlock = this.collisionBlocks[i]
            // if the player is colliding with a collision block
            if (this.hitbox.position.x <= collisionBlock.position.x + collisionBlock.width && 
                this.hitbox.position.x + this.hitbox.width >= collisionBlock.position.x && 
                this.hitbox.position.y + this.hitbox.height >= collisionBlock.position.y &&
                this.hitbox.position.y <= collisionBlock.position.y + collisionBlock.height
            ) {
                // collision on the left
                if (this.velocity.y < 0) {
                    this.velocity.y = 0
                    const offset = this.hitbox.position.y - this.position.y
                    this.position.y = collisionBlock.position.y + collisionBlock.height - offset + 0.01
                    break
                }

                if (this.velocity.y > 0) {
                    this.velocity.y = 0
                    const offset = this.hitbox.position.y - this.position.y + this.hitbox.height
                    this.position.y = collisionBlock.position.y - offset - 0.01
                    break
                }
            }   
        }
    }
}