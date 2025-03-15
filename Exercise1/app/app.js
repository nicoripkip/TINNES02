const express   = require("express")
const app       = express()
const PORT      = 8080


app.set("view engine", "ejs")
app.set("views", __dirname)


app.get("/", (req, res) => {
    res.render("index")
})


app.listen(PORT, () => {
    console.log(`Listening at https://localhost:${PORT}`)
})