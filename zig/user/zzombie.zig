const c = @cImport({
    @cInclude("types.h");
    @cInclude("stat.h");
    @cInclude("user.h");
});
const fork = c.fork;
const sleep = c.sleep;
const exit = c.exit;

export fn main() void {
    if (fork() > 0) {
        _ = sleep(5);
    }
    exit();
}
