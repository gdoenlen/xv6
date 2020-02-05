const c = @cImport({
    @cInclude("types.h");
    @cInclude("user.h");
});

export fn main() void {
    c.printf(2, "hello world\n");
    c.exit();
}
