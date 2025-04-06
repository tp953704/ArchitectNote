// SPDX-License-Identifier: MIT 

pragma solidity >=0.8.0;

contract Property{
    int public value;

    /// 常數不會變更 需要預設
    string constant public location = "USA"
    function setValue(int _value) public{
        value = _value;
    }

    // 声明这个函数是纯函数, 因为它不涉及区块链｡
    // 它既不修改区块链, 也不读取区块｡
    // 用的也是局部變量
    function f1() public pure returns(int){
        int x =5;
        x=x*2;
        return x;
    }
}