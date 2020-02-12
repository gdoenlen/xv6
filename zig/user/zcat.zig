const c = @cImport({
    @cInclude("types.h");
    @cInclude("stat.h");
    @cInclude("user.h");
});
const exit = c.exit;
const open = c.open;
const printf = c.printf;
const read = c.read;
const write = c.write;
const close = c.close;

export fn main(argc: c_int, argv: [*c][*c]u8) void {
    if (argc <= 1) {
        cat(0);
        exit();
    }

    var i: usize = 1;
    while (i < argc) {
        const fd = open(argv[i], 0);
        if (fd < 0) {
            printf(1, "cat: cannot open %s\n", argv[i]);
        }
        cat(fd);
        _ = close(fd);
        i += 1;
    }
    exit();
}

fn cat(fd: c_int) void {
    var buffer: [512]u8 = undefined;
    var n = read(fd, &buffer, buffer.len);
    while (n > 0) {
        const res = write(1, &buffer, n);
        if (res != n) {
            printf(1, "cat: write error\n");
            exit();
        }
        n = read(fd, &buffer, buffer.len);
    }

    if (n < 0) {
        printf(1, "cat: read error\n");
        exit();
    }
}
