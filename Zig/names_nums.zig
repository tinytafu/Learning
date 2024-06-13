//导入标准库
const std = @import("std");

//定义一个全局常量
const global_constant = 42;
//定义一个全局变量
var global_variable: u16 = 100;

fn printInfo(name: []const u8, x: anytype) void {
    std.debug.print("{s:>10} {any:^10}\t{}\n", .{ name, x, @TypeOf(x) });
}

pub fn main() !void {
    //输出标签
    std.debug.print("{s:>10} {s:^10}\t{s}\n", .{ "name", "value", "type" });
    std.debug.print("{s:>10} {s:^10}\t{s}\n", .{ "----", "----", "----" });
    printInfo("global_constant", global_constant);
    printInfo("global_variable", global_variable);

    //定义一个常量带类型
    const con1: u8 = 10;
    //定义一个常量不带类型
    const con2 = 20;
    printInfo("con1", con1);
    printInfo("con2", con2);
    //定义一个变量带类型 -- 若使用var修饰一个标识符,那么这个标识符必须在后面要被修改
    //否则,就使用const修饰
    var var1: u8 = 10;
    var1 += 1;
    //定义一个变量不带类型
    comptime var var2 = 10;
    var2 -= 1;
    printInfo("var1", var1);
    printInfo("var2", var2);
}
