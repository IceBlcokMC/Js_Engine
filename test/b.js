function b() {
    console.info("b module function called");
    console.log("[B] Current working directory:", process.cwd());
    // console.log("[B] Module paths:", module.paths);
    // console.log("[B] __dirname:", __dirname);
    // console.log("[B] __filename:", __filename);

    // require("./c.js")();
    return true;
}

// module.exports = b;

export {
    b
};