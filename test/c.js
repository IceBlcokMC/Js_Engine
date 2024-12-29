function c() {
    console.info("c module function called");
    // console.log("[C] Current working directory:", process.cwd());
    // console.log("[C] Module paths:", module.paths);
    // console.log("[C] __dirname:", __dirname);
    // console.log("[C] __filename:", __filename);

    return true;
}

module.exports = c;