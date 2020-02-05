const c = @cImport({
    @cInclude("types.h");
    @cInclude("stat.h");
    @cInclude("user.h");
});
const printf = c.printf;
const exit = c.exit;
const kill = c.kill;
const atoi = c.atoi;

export fn main(argc: c_int, argv: [*c][*c]u8) void {
    if (argc < 2) {
        printf(2, "usage: kill pid...\n");
        exit();
    }

    var i: usize = 1;
    while (i < argc) {
        var result = kill(atoi(argv[i]));
        if (result > 0) {
            printf(2, "failed to kill pid: %d", result);
        }
        i += 1;
    }
    exit();
}
