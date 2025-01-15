/// <reference path="../index.d.ts"/>

declare namespace Enums {
    /** 命令的执行权限 */
    enum PermissionDefault {
        /** 所有人都可以执行 */
        True = 0,
        /** 玩家不可执行 */
        False = 1,
        /** 仅管理员可执行 */
        Operator = 2,
        /** 仅玩家可执行 */
        NotOperator = 3
    }
}