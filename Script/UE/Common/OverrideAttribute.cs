﻿using System;

namespace Script.Common
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    public class OverrideAttribute : Attribute
    {
    }
}