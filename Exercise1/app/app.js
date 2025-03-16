const express   = require("express")
const path      = require("path")
const mqtt      = require("mqtt")
const app       = express()
const PORT      = 80


app.set("view engine", "ejs")
app.set("views", __dirname) 


app.use(express.static(path.join(__dirname, "../public")))


app.get("/", (req, res) => {
    res.render("index")
})


app.listen(PORT, () => {
    console.log(`Listening at https://localhost:${PORT}`)
})