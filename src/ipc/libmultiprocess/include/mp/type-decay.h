// Copyright (c) The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef MP_PROXY_TYPE_DECAY_H
#define MP_PROXY_TYPE_DECAY_H

#include <mp/util.h>

namespace mp {
template <typename LocalType, typename Value, typename Output>
void CustomBuildField(TypeList<const LocalType>,
    Priority<0>,
    InvokeContext& invoke_context,
    Value&& value,
    Output&& output)
{
    BuildField(TypeList<LocalType>(), invoke_context, output, std::forward<Value>(value));
}

template <typename LocalType, typename Value, typename Output>
void CustomBuildField(TypeList<LocalType&>, Priority<0>, InvokeContext& invoke_context, Value&& value, Output&& output)
{
    BuildField(TypeList<LocalType>(), invoke_context, output, std::forward<Value>(value));
}

template <typename LocalType, typename Value, typename Output>
void CustomBuildField(TypeList<LocalType&&>,
    Priority<0>,
    InvokeContext& invoke_context,
    Value&& value,
    Output&& output)
{
    BuildField(TypeList<LocalType>(), invoke_context, output, std::forward<Value>(value));
}
} // namespace mp

#endif // MP_PROXY_TYPE_DECAY_H
