Array.prototype.parse2D = function() {
    const rows = []
    for (let i = 0; i < this.length; i += 16) {
        rows.push(this.slice(i, i + 16))
    }
    return rows
}

Array.prototype.createObjectsFrom2D = function() {
    const objets = []
    this.forEach((row, y) => {
        row.forEach((symbol, x) => {
            if (symbol === 292) {
                // push a new collision block into the collisions array
                objets.push(
                    new CollisionBlock({
                        position: {
                            x: x * 64,
                            y: y * 64,
                        }
                    })
                ) 
            }
        })
    })
    return objets
}