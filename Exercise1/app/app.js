const express   = require("express")
const path      = require("path")
const https     = require("https")
const http      = require("http")
const fs        = require("fs")


const app       = express()
const PORT      = 443
const options   = {
    key: fs.readFileSync(path.join(__dirname, "../certs/key.pem")),
    cert: fs.readFileSync(path.join(__dirname, "../certs/cert.pem"))
}


app.set("view engine", "ejs")
app.set("views", __dirname) 


app.use(express.static(path.join(__dirname, "../public")))


app.get("/", (req, res) => {
    res.render("index")
})


https.createServer(options, app).listen(PORT, () => {
    console.log(`Server is listening on: https://localhost:${PORT}`)
})