const std = @import("std");

const src = [_][]const u8 {
    "main.c",
    "aabb.c",
    "sat.c",
    "array.c",
    "physics.c",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const raylib_dep = b.dependency("raylib", .{
        .optimize = optimize,
        .target = target,
    });
    const raylib_artifact = raylib_dep.artifact("raylib");

    const exe = b.addExecutable(.{
        .name = "Colliders",
        .root_module = b.createModule(.{
            .optimize = optimize,
            .target = target,
            .link_libc = true,
        }),
    });

    exe.addCSourceFiles(.{
        .root = b.path("src/"),
        .files = &src,
        .flags = &.{
            "-fsanitize=address",
        },
    });

    switch (target.result.os.tag) {
        .linux => {
            exe.linkSystemLibrary("asan");
        },
        else => {},
    }

    exe.installLibraryHeaders(raylib_artifact);
    exe.linkLibrary(raylib_artifact);

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
