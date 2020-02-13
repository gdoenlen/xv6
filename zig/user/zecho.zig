const c = @cImport({
    @cInclude("types.h");
    @cInclude("stat.h");
    @cInclude("user.h");
});
const printf = c.printf;
const exit = c.exit;

export fn main(argc: c_int, argv: [*c][*c]u8) void {
    var i: usize = 1;
    while (i < argc) {
        const eol: *const [1:0]u8 = if ((i + 1) > argc) " " else "\n";

        printf(1, "%s%s", argv[i], eol);
        i += 1;
    }
    exit();
}
